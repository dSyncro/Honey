#include "Context.h"

#include "../ArgumentParser/ArgumentParser.h"

using namespace Honeypot;

Context::Context(int argc, char** argv)
{
	ArgumentParser parser(argc, argv);
	parser.AddPositionalArgument(Argument("Tests", Argument::ZEROORMORE, "Tests to be performed."));
	parser.AddFlag(Flag("c", "categories", Flag::ONEORMORE, "Used to specify entire categories to perform the testing of."));
	parser.AddFlag(Flag("t", "tests", Flag::ONEORMORE, "Used to specify tests to be performed."));

	try { parser.Parse(); }
	catch (...) { parser.PrintHelp(); }

	_tests = parser.GetPositionalValueByName("Tests");
	_categories = parser.GetFlagValueByName("c");
}

void Context::Run()
{
	Console::WriteLine("---- Test Results ----");
	Console::NewLine();

	if (_tests.size() || _categories.size())
		RunSelected();
	else RunAll();
}

void Context::ReportTest(const std::shared_ptr<TestCase>& test)
{
	Console::Write("Test \"", test->Name, "\" (", test->File, "): ");

	if (test->Passed)
	{
		Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "Passed!");
		return;
	}

	Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Failed!");
	Console::WriteColoredLine(AnsiStyle::Forecolors::Red, test->ErrorLog);
}

void Context::ReportTest(const std::shared_ptr<TestCase>& test, std::size_t& failed, std::size_t& passed)
{
	Console::Write("Test \"", test->Name, "\" (", test->File, "): ");

	if (test->Passed)
	{
		Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "Passed!");
		passed++;
		return;
	}

	Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Failed!");
	Console::WriteColoredLine(AnsiStyle::Forecolors::Red, test->ErrorLog);
	failed++;
}

void Context::RecursiveWalkSubcategory(const std::shared_ptr<TestCategory>& category, std::string parentCategoryName, std::size_t depth)
{
	std::string categoryName = parentCategoryName;
	if (parentCategoryName.length())
	{
		Console::WriteColored(AnsiStyle::Forecolors::Cyan, "Subcategory: ");
		categoryName += " > ";
	}
	else Console::WriteColored(AnsiStyle::Forecolors::Cyan, "Category: ");
	categoryName += category->Name;

	Console::WriteColoredLine(AnsiStyle::Forecolors::Cyan, categoryName);

	for (const std::shared_ptr<TestCase>& test : category->GetRegisteredTestCases())
		ReportTest(test);

	for (const std::shared_ptr<TestCategory>& subcategory : category->GetRegisteredTestCategories())
	{
		Console::NewLine();
		RecursiveWalkSubcategory(subcategory, categoryName, depth + 1);
	}
}

void Context::RecursiveSelect(const std::shared_ptr<TestCategory>& category, std::vector<std::shared_ptr<TestCase>>& selectedTests, std::vector<std::shared_ptr<TestCategory>>& selectedCategories)
{
	for (const std::shared_ptr<TestCase>& test : category->GetRegisteredTestCases())
	{
		for (std::size_t i = 0; i < _tests.size(); i++)
			if (_tests[i] == test->Name) { selectedTests.push_back(test); break; }
	}

	for (const std::shared_ptr<TestCategory>& subcategory : category->GetRegisteredTestCategories())
	{
		bool found = false;
		for (std::size_t i = 0; i < _categories.size(); i++)
			if (_categories[i] == subcategory->Name) { found = true; break; }

		if (found) { selectedCategories.push_back(subcategory); }
		else { RecursiveSelect(subcategory, selectedTests, selectedCategories); }
	}
}

void Context::RunSelected()
{
	std::vector<std::shared_ptr<TestCase>> selectedTests;
	std::vector<std::shared_ptr<TestCategory>> selectedCategories;

	for (const std::shared_ptr<TestCategory>& category : GetRegisteredTestCategories())
		RecursiveSelect(category, selectedTests, selectedCategories);

	std::size_t failed = 0;
	std::size_t passed = 0;

	Console::WriteLine("* Singular tests *");
	for (const std::shared_ptr<TestCase>& test : selectedTests)
	{
		test->Run();
		ReportTest(test, failed, passed);
	}
	Console::WriteLine("Passed: ", passed, " ---- Failed: ", failed, " ---- Performed: ", passed + failed);
	Console::NewLine();

	Console::WriteLine("* Categories *");
	for (const std::shared_ptr<TestCategory>& category : selectedCategories)
	{
		category->Run();
		RecursiveWalkSubcategory(category);
		Console::NewLine();
		Console::WriteLine("Passed: ", category->PassedTests, " ---- Failed: ", category->FailedTests, " ---- Performed: ", category->GetPerformedTests());
		Console::NewLine();
	}

	Console::NewLine();
	Console::WriteLine("---- Categories Summary ----");
	Console::NewLine();
	for (const std::shared_ptr<TestCategory>& category : selectedCategories)
	{
		Console::Write(category->Name, ": ");
		if (category->FailedTests)
			Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Failed!");
		else Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "Passed!");
	}
}

void Context::RunAll()
{
	for (const std::shared_ptr<TestCategory>& category : GetRegisteredTestCategories())
	{
		category->Run();
		RecursiveWalkSubcategory(category);

		Console::NewLine();
		std::shared_ptr<TestCategory> baseCategory = GetTestCategory();
		Console::WriteLine("Passed: ", baseCategory->PassedTests, " ---- Failed: ", baseCategory->FailedTests, " ---- Performed: ", baseCategory->GetPerformedTests());
		Console::NewLine();
	}

	Console::NewLine();
	Console::WriteLine("---- Categories Summary ----");
	Console::NewLine();
	for (const std::shared_ptr<TestCategory>& category : GetRegisteredTestCategories())
		PrintCategoriesSummaryTree(category);
}

void Context::PrintCategoriesSummaryTree(const std::shared_ptr<TestCategory>& category, std::string indent, bool isLast)
{
	std::string marker = isLast ? "`---" : "|---";

	Console::Write(indent);
	if (!indent.empty()) Console::Write(marker);

	// Write Node
	Console::Write(category->Name, ": ");
	if (category->FailedTests)
		Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Failed!");
	else Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "Passed!");

	indent += isLast ? "    " : "|   ";

	std::vector<std::shared_ptr<TestCategory>>& subcategories = category->GetRegisteredTestCategories();
	for (std::size_t i = 0; i < subcategories.size(); i++)
		PrintCategoriesSummaryTree(subcategories[i], indent, i == subcategories.size() - 1);
}

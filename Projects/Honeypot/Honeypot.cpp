#include "Honeypot.h"

#include "ArgumentParser/ArgumentParser.h"
#include "ArgumentParser/Exceptions.h"

#include <iostream>

class Context {

public:

	Context() = default;
	Context(int argc, char** argv)
	{
		ArgumentParser parser(argc, argv);
		parser.AddPositionalArgument(Argument("Tests", Argument::ZEROORMORE, "Tests to be performed."));
		parser.AddFlag(Flag("c", "categories", Flag::ONEORMORE, "Used to specify entire categories to perform the testing of."));
		parser.AddFlag(Flag("t", "tests", Flag::ONEORMORE, "Used to specify tests to be performed."));
		
		try { parser.Parse(); }
		catch(...) { parser.PrintHelp(); }

		_tests = parser.GetPositionalValueByName("Tests");
		_categories = parser.GetFlagValueByName("c");
	}

	void Run()
	{
		_reportData.Reset();

		Console::WriteLine("---- Test Results ----");

		if (_tests.size() || _categories.size())
			RunSelected();
		else RunAll();

		Console::NewLine();
		Console::WriteLine("Passed: ", _reportData.Passed, " ---- Failed: ", _reportData.Failed, " ---- Performed: ", _reportData.GetPerformed());
	}

private:

	void ReportTest(const std::shared_ptr<TestCase>& test)
	{
		Console::Write("Test \"", test->Name, "\" (", test->File, "): ");

		if (test->Passed)
		{
			Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "Passed!");
			_reportData.Passed++;
			return;
		}

		Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Failed!");
		Console::WriteColoredLine(AnsiStyle::Forecolors::Red, test->ErrorLog);
		_reportData.Failed++;
	}

	void RecursiveWalkSubcategory(const std::shared_ptr<TestCategory>& category, std::string parentCategoryName = "", std::size_t depth = 0)
	{
		Console::NewLine();
		std::string categoryName = parentCategoryName;
		if (parentCategoryName.length()) categoryName += " > ";
		categoryName += category->Name;

		Console::WriteColoredLine(AnsiStyle::Forecolors::Cyan, categoryName);

		for (const std::shared_ptr<TestCase>& test : category->GetRegisteredTestCases())
		{
			ReportTest(test);
		}

		for (const std::shared_ptr<TestCategory>& subcategory : category->GetRegisteredTestCategories())
			RecursiveWalkSubcategory(subcategory, categoryName, depth + 1);
	}

	void RecursiveSelectAllTests(const std::shared_ptr<TestCategory>& category, std::vector<std::shared_ptr<TestCase>>& selected)
	{
		for (const std::shared_ptr<TestCase>& test : category->GetRegisteredTestCases())
			selected.push_back(test);

		for (const std::shared_ptr<TestCategory>& subcategory : category->GetRegisteredTestCategories())
			RecursiveSelectAllTests(subcategory, selected);
	}

	void RecursiveSelectTests(const std::shared_ptr<TestCategory>& category, std::vector<std::shared_ptr<TestCase>>& selected)
	{
		for (const std::shared_ptr<TestCase>& test : category->GetRegisteredTestCases())
		{
			for (std::size_t i = 0; i < _tests.size(); i++)
				if (_tests[i] == test->Name) { selected.push_back(test); break; }
		}

		for (const std::shared_ptr<TestCategory>& subcategory : category->GetRegisteredTestCategories())
		{
			bool found = false;
			for (std::size_t i = 0; i < _categories.size(); i++)
				if (_categories[i] == subcategory->Name) { found = true; break; }

			if (found) { RecursiveSelectAllTests(subcategory, selected); }
			else { RecursiveSelectTests(subcategory, selected); }
		}
	}

	void RunSelected()
	{
		std::vector<std::shared_ptr<TestCase>> selectedTests;

		for (const std::shared_ptr<TestCategory>& category : GetRegisteredTestCategories())
			RecursiveSelectTests(category, selectedTests);

		for (const std::shared_ptr<TestCase>& test : selectedTests)
		{
			test->Run();
			ReportTest(test);
		}
	}

	void RunAll()
	{
		for (const std::shared_ptr<TestCategory>& category : GetRegisteredTestCategories())
		{
			category->Run();
			RecursiveWalkSubcategory(category);
		}
	}

	std::vector<std::string> _tests;
	std::vector<std::string> _categories;

	TestReportData _reportData;

};

int main(int argc, char** argv)
{
	Context(argc, argv).Run();
}

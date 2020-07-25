#include "Honeypot.h"

#include "ArgumentParser/ArgumentParser.h"
#include "ArgumentParser/Exceptions.h"

#include <iostream>

using namespace Honeypot;

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
        TestReportData data = TestReportData();
        std::set<TestCase> tests = !(_tests.size() || _categories.size()) ? GetRegisteredTests() : GetSelectedTests();
        data.Total = tests.size();

        // Perform tests
        Console::WriteLine("Performing Tests...");
        for (const TestCase& test : tests)
        {
            SetCurrentTestCase(test);

            Console::WriteColored(AnsiStyle::Forecolors::Yellow, '"', test.Name, '"',
                '[', test.Line, "] (", test.File, "): ");

            test.Callback();

            if (GetCurrentTestCase().HasFailed) 
            { 
                Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Failed!");
                data.Failed++;
            }
            else Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "Succeded!");

            GetCurrentTestCase().GetCategory().PerformedTests++;
            data.Performed++;
        }

        Console::NewLine();
        for (const TestCategory* category : GetRegisteredTestCategories())
        {
            Console::WriteLine("From \"", category->Name, "\": ");
            Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "    Total Tests ", category->Tests);
            AnsiStyle::Forecolors color = category->Tests == category->PerformedTests ?
                AnsiStyle::Forecolors::Green : AnsiStyle::Forecolors::Yellow;
            Console::WriteColoredLine(color, "    Performed ", category->PerformedTests);
            Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "    Failed ", category->FailedTests);
        }

        Console::NewLine();

        Console::WriteLine("Total tests: ", data.Total);
        Console::WriteLine("Performed tests: ", data.Performed);
        Console::WriteLine("Succeded tests: ", data.GetSucceded());
        Console::WriteLine("Failed tests: ", data.Failed);
    }

private:

    std::set<TestCase> GetSelectedTests()
    {
        // Get all tests
        std::set<TestCase> tests = GetRegisteredTests();
        std::size_t totalTests = tests.size();
        for (auto it = tests.begin(); it != tests.end(); )
        {
            bool found = false;

            for (std::size_t i = 0; i < _tests.size(); i++)
                if (_tests[i] == it->Name) { found = true; break; }

            if (found) continue;

            for (std::size_t i = 0; i < _categories.size(); i++)
                if (_categories[i] == it->GetCategory().Name) { found = true; break; }

            if (!found) it = tests.erase(it);
            else it++;
        }

        return tests;
    }

    std::vector<std::string> _tests;
    std::vector<std::string> _categories;

};

int main(int argc, char** argv)
{
    Context(argc, argv).Run();
}
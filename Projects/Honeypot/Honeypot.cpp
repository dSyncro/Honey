#include "Honeypot.h"

#include <iostream>

using namespace Honeypot;

struct Context {

    void Run()
    {
        const std::set<TestCase>& tests = GetRegisteredTests();
        for (const TestCase& test : tests)
        {
            SetCurrentTestCase(test);

            Console::WriteLine("Test Category: ", test.GetCategory().Name);

            Console::WriteColoredLine(AnsiStyle::Forecolors::Yellow, "Testing - ", '"', test.Name, '"', 
                '[', test.Line, "] (", test.File, "): ");

            test.Callback();

            if (GetCurrentTestCase().HasFailed) Console::WriteColoredLine(AnsiStyle::Forecolors::Red, "Failed!");
            else Console::WriteColoredLine(AnsiStyle::Forecolors::Green, "Succeded!");
        }

        for (const TestCategory* category : GetRegisteredTestCategories())
        {
            Console::WriteLine("Test Category: ", category->Name, " tests ", category->Tests, " fails ", category->FailedTests);
        }
    }

};

int main(int argc, char** argv)
{
    Context().Run();
}
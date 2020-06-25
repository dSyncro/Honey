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
        char* args[] = {
            "ehi.exe",
            "positional1",
            "positional2",
            "-f",
            "-c",
        };

        try
        {
            ArgumentParser parser(5, args);
            parser.AddPositionalArgument(Argument("add", "addition thing", 2));
            parser.AddToggle(Toggle("f", "flag"));
            parser.AddToggle(Toggle("c", "cesso"));
            parser.AddFlag(Flag("k", "kristinadavena"));
            parser.AddFlag(Flag("b", "babbuino"));
            parser.GetToggleValueByName("f");
            parser.GetToggleValueByAlias("flag");
            parser.PrintHelp();
            parser.Parse();
            parser.GetToggleValueByName("f");
            parser.GetToggleValueByAlias("flag");
        }
        catch(const TooManyArgumentsException& ex) {
            std::cout << ex.what() << "\n";
        }
    }

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
    Context(argc, argv).Run();
}
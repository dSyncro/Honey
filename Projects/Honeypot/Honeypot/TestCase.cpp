#include "TestCase.h"

TestCase::TestCase() : Name(""), Description(""), File("") {}

TestCase::TestCase(const std::string& name, const std::string& description, const std::string& file)
    : Name(name), Description(description), File(file) { }

void TestCase::Run()
{
	Passed = true;
	Callback();
}

void TestCase::CheckTrue(bool actual, std::size_t line)
{
	if (actual) return;

	Passed = false;
	ErrorLog += "Bool check failed at line " + std::to_string(line) + ".\n"
		"Expected: true";
}

void TestCase::CheckTrue(bool actual, std::size_t line, const std::string& actualCode)
{
	if (actual) return;

	Passed = false;
	ErrorLog += "Bool check failed at line " + std::to_string(line) + ".\n"
		"Expected: true" + "\n"
		"Code: " + actualCode;
}

void TestCase::CheckFalse(bool actual, std::size_t line)
{
	if (!actual) return;

	Passed = false;
	ErrorLog += "Bool check failed at line " + std::to_string(line) + ".\n"
		"Expected: false";
}

void TestCase::CheckFalse(bool actual, std::size_t line, const std::string& actualCode)
{
	if (!actual) return;

	Passed = false;
	ErrorLog += "Bool check failed at line " + std::to_string(line) + ".\n"
		"Expected: false" + "\n"
		"Code: " + actualCode;
}

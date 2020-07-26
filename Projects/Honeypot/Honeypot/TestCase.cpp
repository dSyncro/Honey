#include "TestCase.h"

TestCase::TestCase() : Name(""), Description(""), File("") {}

TestCase::TestCase(const std::string& name, const std::string& description, const std::string& file)
    : Name(name), Description(description), File(file) { }

bool TestCase::operator <(const TestCase& other) const
{
    return File < other.File;
}
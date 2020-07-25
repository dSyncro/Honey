#include "TestCase.h"

using namespace Honeypot;

TestCase::TestCase() : Name(nullptr), Callback(nullptr), File(nullptr), Line(0), _category(&(::GetTestCategory())) {}

TestCase::TestCase(const char* name, CallbackType callback, const char* file, unsigned line, TestCategory& category)
    : Name(name), Callback(callback), File(file), Line(line), _category(&category)
{
    _category->Tests++;
}

void TestCase::MarkFailure()
{
    HasFailed = true;
    _category->FailedTests++;
}

bool TestCase::operator <(const TestCase& other) const
{
    if (Line != other.Line)
        return Line < other.Line;
    const int file_cmp = std::strcmp(File, other.File);
    return file_cmp < 0;
}
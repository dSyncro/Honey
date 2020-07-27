#include "TestCategory.h"

TestCategory::TestCategory(const std::string& name, const std::string& description) : Name(name), Description(description) {}

void TestCategory::Run()
{
	PassedTests = 0;
	FailedTests = 0;

	for (std::shared_ptr<TestCategory>& category : _subcategories)
	{
		category->Run();
		PassedTests += category->PassedTests;
		FailedTests += category->FailedTests;
	}

	for (std::shared_ptr<TestCase>& test : _cases)
	{
		test->Run();
		if (test->Passed) PassedTests++;
		else FailedTests++;
	}
}

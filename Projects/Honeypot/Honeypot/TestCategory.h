#pragma once

#include "TestCase.h"

#include <string>
#include <memory>
#include <vector>

struct TestCategory
{
	std::string Name;
	std::string Description;
	std::size_t PassedTests = 0;
	std::size_t FailedTests = 0;

	std::size_t GetPerformedTests() const noexcept { return PassedTests + FailedTests; }

	TestCategory(const std::string& name = "", const std::string& description = "");

	std::vector<std::shared_ptr<TestCategory>>& GetRegisteredTestCategories() noexcept { return _subcategories; }
	std::vector<std::shared_ptr<TestCase>>& GetRegisteredTestCases() noexcept { return _cases; }
	int RegisterTestCase(const std::shared_ptr<TestCase>& test) noexcept { _cases.push_back(test); return 0; }
	int RegisterTestCategory(const std::shared_ptr<TestCategory>& category) noexcept { _subcategories.push_back(category); return 0; }

	void Run();

private:

	std::vector<std::shared_ptr<TestCategory>> _subcategories;
	std::vector<std::shared_ptr<TestCase>> _cases;
};

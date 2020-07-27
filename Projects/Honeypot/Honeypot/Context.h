#pragma once

#include "../Honeypot.h"

namespace Honeypot {

	class Context {

	public:

		Context() = default;
		Context(int argc, char** argv);

		void Run();

	private:

		void RunSelected();
		void RunAll();

		void RecursiveWalkSubcategory(const std::shared_ptr<TestCategory>& category, std::string parentCategoryName = "", std::size_t depth = 0);
		void RecursiveSelect(const std::shared_ptr<TestCategory>& category, std::vector<std::shared_ptr<TestCase>>& selectedTests, std::vector<std::shared_ptr<TestCategory>>& selectedCategories);

		static void ReportTest(const std::shared_ptr<TestCase>& test);
		static void ReportTest(const std::shared_ptr<TestCase>& test, std::size_t& failed, std::size_t& passed);

		static void PrintCategoriesSummaryTree(const std::shared_ptr<TestCategory>& category, std::string indent = "", bool isLast = true);

		std::vector<std::string> _tests;
		std::vector<std::string> _categories;

	};

}

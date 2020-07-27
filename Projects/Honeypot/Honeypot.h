#pragma once

#include "Honeypot/Core.h"
#include "Honeypot/TestCategory.h"

inline std::vector<std::shared_ptr<TestCategory>>& GetRegisteredTestCategories()
{
	static std::vector<std::shared_ptr<TestCategory>> categories;
	return categories;
}

inline int RegisterTestCategory(const std::shared_ptr<TestCategory>& category)
{
	GetRegisteredTestCategories().push_back(category);
	return 0;
}

inline std::shared_ptr<TestCategory> GetTestCategory()
{
	static std::shared_ptr<TestCategory> category = std::make_shared<TestCategory>();
	static bool init = false;
	if (!init)
	{
		category->Name = "All Tests";
		category->Description = "Here is where all the tests will be put.";
		init = true;
		RegisterTestCategory(category);
	}
	return category;
}

#define HNYPT_CATEGORY_NAMESPACE(name) HNYPT_CONCAT(TestNamespace, HNYPT_LINE_ID(name))
#define HNYPT_CASE_CLASS(name) HNYPT_CONCAT(TestClass, HNYPT_LINE_ID(name))
#define HNYPT_CASE_INSTANCE(name) HNYPT_CONCAT(TestInstance, HNYPT_LINE_ID(name))

#define HNYPT_TEST_CATEGORY(catName, catDescription) namespace HNYPT_CATEGORY_NAMESPACE(catName) { \
		inline std::shared_ptr<TestCategory> GetTestCategory() {                                   \
			static std::shared_ptr<TestCategory> category = std::make_shared<TestCategory>();      \
			static bool init = false;                                                              \
			if (!init)                                                                             \
			{                                                                                      \
				category->Name = HNYPT_TOSTRING(catName);                                          \
				category->Description = catDescription;                                            \
				init = true;                                                                       \
			}                                                                                      \
			return category;                                                                       \
		}                                                                                          \
	}                                                                                              \
	static int HNYPT_SINGULAR(_HNYPT_ANON_VAR_) = GetTestCategory()->RegisterTestCategory(HNYPT_CATEGORY_NAMESPACE(catName)::GetTestCategory()); \
	namespace HNYPT_CATEGORY_NAMESPACE(catName)

#define HNYPT_TEST_CASE(testName, testDescription) class HNYPT_CASE_CLASS(testName) : public TestCase \
{                                                                                                     \
public:                                                                                               \
	HNYPT_CASE_CLASS(testName) (const std::string& name, const std::string& description)              \
	: TestCase(name, description, __FILE__) {  }                                                      \
	virtual void Callback();                                                                          \
protected:                                                                                            \
	HNYPT_CASE_CLASS(testName) (const HNYPT_CASE_CLASS(testName)& src) : TestCase(src) { }            \
};                                                                                                    \
static std::shared_ptr<HNYPT_CASE_CLASS(testName)> HNYPT_CASE_INSTANCE(testName) = std::make_shared<HNYPT_CASE_CLASS(testName)>(HNYPT_TOSTRING(testName), testDescription); \
static int HNYPT_SINGULAR(_HNYPT_ANON_VAR_) = GetTestCategory()->RegisterTestCase(HNYPT_CASE_INSTANCE(testName));                                                           \
void HNYPT_CASE_CLASS(testName)::Callback()

#define HNYPT_TEST_CASE_NODESCR(testName) HNYPT_TEST_CASE(testName, "")
#define HNYPT_TEST_CATEGORY_NODESCR(catName) HNYPT_TEST_CATEGORY(catName, "")

#define HNYPT_CHECK(code) CheckTrue(code, __LINE__, HNYPT_TOSTRING(code));
#define HNYPT_CHECK_TRUE(code) CheckTrue(code, __LINE__, HNYPT_TOSTRING(code));
#define HNYPT_CHECK_FALSE(code) CheckFalse(code, __LINE__, HNYPT_TOSTRING(code));
#define HNYPT_CHECK_EQUAL(actual, expected) CheckEqual(actual, expected, __LINE__, HNYPT_TOSTRING(actual), HNYPT_TOSTRING(expected));

//Alias
#define TEST_CASE(name, description) HNYPT_TEST_CASE(name, description)
#define TEST_CATEGORY(name, description) HNYPT_TEST_CATEGORY(name, description)
#define TEST_CASE_NODESCR(name) HNYPT_TEST_CASE(name, "")
#define TEST_CATEGORY_NODESCR(name) HNYPT_TEST_CATEGORY(name, "")
#define CHECK(code) HNYPT_CHECK(code)
#define CHECK_TRUE(code) HNYPT_CHECK_TRUE(code)
#define CHECK_FALSE(code) HNYPT_CHECK_FALSE(code)
#define CHECK_EQUAL(actual, expected) HNYPT_CHECK_EQUAL(actual, expected)
//#define EXCEPTION(code, exception) HNYPT_CHECK_EXCEPTION(code, exception)
//#define NO_EXCEPTION(code) HNYPT_CHECK_NO_EXCEPTION(code)

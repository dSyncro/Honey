#pragma once

#include <set>

namespace Honeypot {

    struct TestCategory
    {
        const char* Name;
        const char* Description;
        unsigned int Tests = 0;
        unsigned int FailedTests = 0;
        bool HasFailed = false;

        TestCategory(const char* name = "", const char* description = "");
    };

    inline std::set<TestCategory*>& GetRegisteredTestCategories()
    {
        static std::set<TestCategory*> data;
        return data;
    }

    inline void RegisterTestCategory(TestCategory& category)
    {
        GetRegisteredTestCategories().insert(&category);
    }

}

inline Honeypot::TestCategory& GetTestCategory()
{
    static Honeypot::TestCategory category;
    static bool init = false;
    if (!init)
    {
        category.Name = "No Category";
        category.Description = "Tests not belonging to a particular category.";
        init = true;
        Honeypot::RegisterTestCategory(category);
    }
    return category;
}
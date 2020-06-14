#pragma once

#include "TestCategory.h"

namespace Honeypot {

    using CallbackType = void (*)();

    struct TestCase
    {
        const char* Name;
        CallbackType Callback; // a function pointer to the test case
        const char* File;
        unsigned int Line;
        bool HasFailed = false;

        TestCase();
        TestCase(const char* name, CallbackType callback, const char* file, unsigned line, TestCategory& category);

        void MarkFailure();

        bool operator <(const TestCase& other) const;

        const TestCategory& GetCategory() const { return *_category; }

    private:

        TestCategory* _category;
    };

    inline TestCase& GetCurrentTestCase()
    {
        static TestCase data;
        return data;
    }

    inline void SetCurrentTestCase(const TestCase& test)
    {
        GetCurrentTestCase() = test;
    }

    inline std::set<TestCase>& GetRegisteredTests()
    {
        static std::set<TestCase> data;
        return data;
    }

    inline int RegisterTest(const TestCase& test)
    {
        GetRegisteredTests().insert(test);
        return 0;
    }

}
#pragma once

#include "Honeypot/Core.h"
#include "Honeypot/TestCase.h"

struct TestReportData
{
    std::size_t Total;
    std::size_t Performed;
    std::size_t Failed;
    std::size_t GetSucceded() const { return Performed - Failed; }
};

#define HNYPT_REGISTER_FUNCTION(global_prefix, function, name)  \
    global_prefix static int HNYPT_SINGULAR(_HNYPT_ANON_VAR_) = \
    Honeypot::RegisterTest(Honeypot::TestCase( name, function, __FILE__, __LINE__, GetTestCategory() ));

#define HNYPT_CREATE_AND_REGISTER_FUNCTION(function, name)                                        \
    static void function();                                                                       \
    HNYPT_REGISTER_FUNCTION(HNYPT_NOTHING, function, name)                                        \
    static void function()

#define HNYPT_TEST_CASE(name)                                                                     \
    HNYPT_CREATE_AND_REGISTER_FUNCTION(HNYPT_SINGULAR(_HNYPT_ANON_FUNC_), name)

#define HNYPT_CHECK_EXCEPTION(code, exception) do {                              \
        try { code; }                                                            \
        catch (exception&) {}                                                    \
        catch (...) {                                                            \
            HNYPT_ASSERT(false, std::string("Not thrown <") +                    \
            HNYPT_TOSTRING(exception) + "> as expected");                        \
            Honeypot::GetCurrentTestCase().MarkFailure();                        \
            break;                                                               \
        }                                                                        \
        HNYPT_ASSERT(false, "No exception thrown, expected <",                   \
            HNYPT_TOSTRING(exception), "> at line " + std::to_string(__LINE__)); \
        Honeypot::GetCurrentTestCase().MarkFailure();                            \
    } while (false)

#define HNYPT_CHECK_NO_EXCEPTION(code) do {                                      \
        try { code; }                                                            \
        catch (...) {                                                            \
            HNYPT_ASSERT(false, std::string("Thrown <") +                        \
            HNYPT_TOSTRING(exception) + "> at line" + std::to_string(__LINE__)); \
            Honeypot::GetCurrentTestCase().MarkFailure();                        \
            break;                                                               \
        }                                                                        \
    } while (false)

#define HNYPT_CHECK(code) if (!(code)) {                              \
        HNYPT_ASSERT(false, std::string("'") + HNYPT_TOSTRING(code) + \
            "' is false at line " + std::to_string(__LINE__));        \
        Honeypot::GetCurrentTestCase().MarkFailure();                 \
    }

#define HNYPT_TEST_CATEGORY_IMPL(name, description, ns_name) namespace ns_name { \
        inline Honeypot::TestCategory& GetTestCategory() {                    \
            static Honeypot::TestCategory category;                           \
            static bool init = false;                                         \
            if (!init)                                                        \
            {                                                                 \
                category.Name = name;                                         \
                category.Description = description;                           \
                init = true;                                                  \
                Honeypot::RegisterTestCategory(category);                     \
            }                                                                 \
            return category;                                                  \
        }                                                                     \
    }                                                                         \
    namespace ns_name

#define HNYPT_TEST_CATEGORY(name, description) HNYPT_TEST_CATEGORY_IMPL(name, description, HNYPT_SINGULAR(_HNYPT_ANON_SUITE_))

//Alias
#define TEST_CASE(name) HNYPT_TEST_CASE(name)
#define TEST_CATEGORY(name, description) HNYPT_TEST_CATEGORY(name, description)
#define CHECK(code) HNYPT_CHECK(code)
#define EXCEPTION(code, exception) HNYPT_CHECK_EXCEPTION(code, exception)
#define NO_EXCEPTION(code) HNYPT_CHECK_NO_EXCEPTION(code)
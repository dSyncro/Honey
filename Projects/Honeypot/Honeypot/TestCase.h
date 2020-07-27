#pragma once

#include <string>
#include <memory>

using CallbackType = void (*)();

struct TestCase
{
    std::string Name;
    std::string Description;
    std::string File;
    std::string ErrorLog;
    bool Passed = true;

    TestCase();
    TestCase(const std::string& name, const std::string& description, const std::string& file);

	void Run();

	void CheckTrue(bool actual, std::size_t line);
	void CheckTrue(bool actual, std::size_t line, const std::string& actualCode);

	void CheckFalse(bool actual, std::size_t line);
	void CheckFalse(bool actual, std::size_t line, const std::string& actualCode);

    template <typename T>
    void CheckEqual(const T& actual, const T& expected, std::size_t line)
    {
        if (actual == expected) return;

        Passed = false;
        ErrorLog += "Equal check failed at line " + std::to_string(line) + ".\n"
            "Address of actual: " + std::to_string(&actual) + "\n"
            "Address of expected: " + std::to_string(&expected);
    }

	template <typename T>
	void CheckEqual(const T& actual, const T& expected, std::size_t line, const std::string& actualCode, const std::string& expectedCode)
	{
		if (actual == expected) return;

		Passed = false;
		ErrorLog += "Equal check failed at line " + std::to_string(line) + ".\n"
			"Address of actual: " + std::to_string(&actual) + "\n"
			"Address of expected: " + std::to_string(&expected)
			"Actual code: " + actualCode +
			"Expected code: " + expectedCode;
	}

    template <typename T>
    void CheckEqual(const T* actual, const T* expected, std::size_t line)
    {
        if (*actual == *expected) return;

        Passed = false;
        ErrorLog += "Equal check failed at line " + std::to_string(line) + ".\n" +
            "Address of actual: " + std::to_string(actual) + "\n" +
            "Address of expected: " + std::to_string(expected);
    }

	template <typename T>
	void CheckEqual(const T* actual, const T* expected, std::size_t line, const std::string& actualCode, const std::string& expectedCode)
	{
		if (actual == expected) return;

		Passed = false;
		ErrorLog += "Equal check failed at line " + std::to_string(line) + ".\n"
			"Address of actual: " + std::to_string(actual) + "\n"
			"Address of expected: " + std::to_string(expected)
			"Actual code: " + actualCode +
			"Expected code: " + expectedCode;
	}


    virtual void Callback() = 0;
};

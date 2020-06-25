#pragma once

#include <string>

struct Argument {

    explicit Argument(const std::string& name, const std::string& description = "", int nargs = 1, bool required = false);

    std::string Name;
    std::string Description;
    int NumberOfArguments;
    bool IsRequired;

};
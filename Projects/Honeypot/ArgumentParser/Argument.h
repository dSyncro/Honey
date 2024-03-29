#pragma once

#include <string>

struct Argument {

    enum SpecialNumberOfArguments {
        ZEROORMORE = -1,
        ONEORMORE = -2
    };

    explicit Argument(const std::string& name, int nargs = 1, const std::string& description = "", bool isRequired = false)
        : Name(name), Description(description), NumberOfArguments(nargs), IsRequired(isRequired) { }

    std::string Name;
    std::string Description;
    int NumberOfArguments;
    bool IsRequired;

};
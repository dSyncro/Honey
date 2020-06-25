#pragma once

#include "Argument.h"

struct Flag {

    explicit Flag(const std::string& commandName, const std::string& commandAlias = "", int nargs = 0, const std::string& description = "", bool required = false);

    std::string CommandName;
    std::string CommandAlias;
    std::string Description;
    int NumberOfArguments;
    bool IsRequired;
};
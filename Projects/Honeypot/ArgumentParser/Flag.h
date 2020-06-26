#pragma once

#include "Argument.h"

struct Flag {

    enum SpecialNumberOfArguments {
        ZEROORMORE = -1,
        ONEORMORE = -2
    };

    explicit Flag(const std::string& commandName, const std::string& commandAlias = "", int nargs = 0, const std::string& description = "", bool isRequired = false)
        : CommandName(commandName), CommandAlias(commandAlias), NumberOfArguments(nargs), Description(description), IsRequired(isRequired) { }

    std::string CommandName;
    std::string CommandAlias;
    std::string Description;
    int NumberOfArguments;
    bool IsRequired;
};
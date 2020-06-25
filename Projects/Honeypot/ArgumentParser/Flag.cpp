#include "Flag.h"

Flag::Flag(const std::string& commandName, const std::string& commandAlias, int nargs, const std::string& description, bool required)
    : CommandName(commandName), CommandAlias(commandAlias), NumberOfArguments(nargs), Description(description), IsRequired(required) { }
#pragma once

#include <string>

struct Toggle {

    explicit Toggle(const std::string& commandName, const std::string& commandAlias = "", const std::string& description = "")
        : CommandName(commandName), CommandAlias(commandAlias), Description(description) { }

    std::string CommandName;
    std::string CommandAlias;
    std::string Description;

};
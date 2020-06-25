#pragma once

#include <string>

struct Toggle {

    explicit Toggle(const std::string& commandName, const std::string& commandAlias = "", const std::string& description = "", bool required = false);

    std::string CommandName;
    std::string CommandAlias;
    std::string Description;
    bool IsRequired;

};
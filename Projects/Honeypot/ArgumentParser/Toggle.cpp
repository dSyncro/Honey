#include "Toggle.h"

Toggle::Toggle(const std::string& commandName, const std::string& commandAlias, const std::string& description, bool required)
	: CommandName(commandName), CommandAlias(commandAlias), Description(description),  IsRequired(required)
{
}
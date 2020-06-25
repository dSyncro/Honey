#include "Argument.h"

Argument::Argument(const std::string& name, const std::string& description, int nargs, bool required)
	: Name(name), Description(description), NumberOfArguments(nargs), IsRequired(required) { }
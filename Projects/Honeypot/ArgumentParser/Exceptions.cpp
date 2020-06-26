#include "Exceptions.h"

ArgumentRequiredException::ArgumentRequiredException(const std::string& name)
{
    _message = "Argument \"" + name + "\" is required.";
}

InsufficientArgumentsProvidedException::InsufficientArgumentsProvidedException(const std::string& name)
{
    _message = "Insufficient arguments provided for Positional Argument or Flag \"" +
        name + "\".";
}

TooManyArgumentsException::TooManyArgumentsException(const std::string& name)
{
    _message = "Too many arguments provided for Positional Argument or Flag \"" +
        name + "\".";
}
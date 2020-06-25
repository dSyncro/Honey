#pragma once

#include <exception>

#include "Argument.h"

struct ArgumentRequiredException : public std::exception {

    ArgumentRequiredException(const std::string& name);
    const char* what() const noexcept { return _message.c_str(); }

private:

    std::string _message;

};

struct InsufficientArgumentsProvidedException : public std::exception {

    InsufficientArgumentsProvidedException(const std::string& name);
    const char* what() const noexcept { return _message.c_str(); }

private:

    std::string _message;

};

struct TooManyArgumentsException : public std::exception {

    TooManyArgumentsException(const std::string& name);
    const char* what() const noexcept { return _message.c_str(); }

private:

    std::string _message;

};

struct ValueNotDefinedException : public std::exception {

    ValueNotDefinedException(const std::string& name);
    const char* what() const noexcept { return _message.c_str(); }

private:

    std::string _message;

};
#include "TidyException.h"

using namespace Honey;

const char* TidyException::what() const noexcept
{
	_whatBuffer = GetType() + '\n' + GetOriginString();
	return _whatBuffer.c_str();
}

std::string TidyException::GetOriginString() const noexcept
{
	std::string out = "[File] " + _filename + '\n' + "[Line] " + std::to_string(_line);
	return out;
}

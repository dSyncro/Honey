#include "AnsiStyle.h"
#include <sstream>

std::string AnsiStyle::CursorNavigation::Move(AnsiStyle::CursorNavigation::Direction direction, unsigned int step) noexcept
{
	std::ostringstream ss;
	ss << "\033[" << static_cast<int>(step) << (char)direction;
	return ss.str();
}
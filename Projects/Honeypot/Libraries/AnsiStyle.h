#pragma once

#include <iostream>
#include <string>

namespace AnsiStyle
{

	const std::string Reset      = "\033[0m";
	const std::string Clear      = "\033[2J";

	enum class Backcolors
	{
		Dark_Black   = 40,
		Dark_Red     = 41,
		Dark_Green   = 42,
		Dark_Yellow  = 43,
		Dark_Blue    = 44,
		Dark_Magenta = 45,
		Dark_Cyan    = 46,
		Dark_White   = 47,

		Reset = 49,

		Black   = 100,
		Red     = 101,
		Green   = 102,
		Yellow  = 103,
		Blue    = 104,
		Magenta = 105,
		Cyan    = 106,
		White   = 107,
	};

	enum class Forecolors
	{
		Dark_Black   = 30,
		Dark_Red     = 31,
		Dark_Green   = 32,
		Dark_Yellow  = 33,
		Dark_Blue    = 34,
		Dark_Magenta = 35,
		Dark_Cyan    = 36,
		Dark_White   = 37,

		Reset = 39,

		Black   = 90,
		Red     = 91,
		Green   = 92,
		Yellow  = 93,
		Blue    = 94,
		Magenta = 95,
		Cyan    = 96,
		White   = 97
	};

	enum class Decorations
	{
		Bold       = 1,
		Dim        = 2,
		Italic     = 3,
		Underline  = 4,
		Blink      = 5,
		RapidBlink = 6,
		Reversed   = 7,
		Conceal    = 8,
		Crossed    = 9
	};

	template <typename T>
	using AnsiToken = typename std::enable_if<
		std::is_same<T, AnsiStyle::Backcolors>::value ||
		std::is_same<T, AnsiStyle::Forecolors>::value ||
		std::is_same<T, AnsiStyle::Decorations>::value,
		std::ostream&>::type;

	template <typename T>
	AnsiToken<T> operator<<(std::ostream& stream, const T& color)
	{
		stream << "\033[" << static_cast<int>(color) << "m";
		return stream;
	}

	namespace CursorNavigation
	{
		const std::string Home = "\033[H";

		enum class Direction : char
		{
			Up    = 'A',
			Down  = 'B',
			Right = 'C',
			Left  = 'D'
		};

		std::string Move(Direction direction, unsigned int step) noexcept;
	}
}
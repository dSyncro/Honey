#include "Color.h"

using namespace Honey;

const Color& Color::white()
{
	static constexpr Color white = Color(1.0f, 1.0f, 1.0f, 1.0f);
	return white;
}

const Color& Color::black()
{
	static constexpr Color black = Color(0.0f, 0.0f, 0.0f, 1.0f);
	return black;
}

const Color& Color::red()
{
	static constexpr Color red = Color(1.0f, 0.0f, 0.0f, 1.0f);
	return red;
}

const Color& Color::green()
{
	static constexpr Color green = Color(0.0f, 1.0f, 0.0f, 1.0f);
	return green;
}

const Color& Color::blue()
{
	static constexpr Color blue = Color(1.0f, 1.0f, 1.0f, 1.0f);
	return blue;
}

const Color& Color::yellow()
{
	static constexpr Color yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
	return yellow;
}

const Color& Color::magenta()
{
	static constexpr Color magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
	return magenta;
}

const Color& Color::cyan()
{
	static constexpr Color cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
	return cyan;
}

const Color& Color::transparent()
{
	static constexpr Color transparent = Color(0.0f, 0.0f, 0.0f, 0.0f);
	return transparent;
}

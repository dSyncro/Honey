#include "../../Honeypot/Core.h"

#include "../Console.h"

using namespace AnsiStyle;

#ifdef HNYPT_PLATFORM_WINDOWS

#include <Windows.h>

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

inline CONSOLE_SCREEN_BUFFER_INFO GetConsoleInfo() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	return info;
}

const CONSOLE_SCREEN_BUFFER_INFO baseConsoleInfo = GetConsoleInfo();

enum class WinConsoleColors {
	Black,
	Blue,
	Green,
	Aqua,
	Red,
	Purple,
	Yellow,
	White,
	Gray,
	LightBlue,
	LightGreen,
	LightAqua,
	LightRed,
	LightPurple,
	LightYellow,
	BrightWhite
};

WinConsoleColors AnsiForegroundToWinColor(Forecolors color)
{
	switch (color)
	{
		case Forecolors::Dark_Black: return WinConsoleColors::Black;
		case Forecolors::Dark_Red: return WinConsoleColors::Red;
		case Forecolors::Dark_Green: return WinConsoleColors::Green;
		case Forecolors::Dark_Yellow: return WinConsoleColors::Yellow;
		case Forecolors::Dark_Blue: return WinConsoleColors::Blue;
		case Forecolors::Dark_Magenta: return WinConsoleColors::Purple;
		case Forecolors::Dark_Cyan: return WinConsoleColors::Aqua;
		case Forecolors::Dark_White: return WinConsoleColors::White;
		case Forecolors::Black: return WinConsoleColors::Gray;
		case Forecolors::Red: return WinConsoleColors::LightRed;
		case Forecolors::Green: return WinConsoleColors::LightGreen;
		case Forecolors::Yellow: return WinConsoleColors::LightYellow;
		case Forecolors::Blue: return WinConsoleColors::LightBlue;
		case Forecolors::Magenta: return WinConsoleColors::LightPurple;
		case Forecolors::Cyan: return WinConsoleColors::LightAqua;
		case Forecolors::White:
		default: return WinConsoleColors::BrightWhite;
	}
}

WinConsoleColors AnsiBackgroundToWinColor(Backcolors color)
{
	switch (color)
	{
		case Backcolors::Dark_Black: return WinConsoleColors::Black;
		case Backcolors::Dark_Red: return WinConsoleColors::Red;
		case Backcolors::Dark_Green: return WinConsoleColors::Green;
		case Backcolors::Dark_Yellow: return WinConsoleColors::Yellow;
		case Backcolors::Dark_Blue: return WinConsoleColors::Blue;
		case Backcolors::Dark_Magenta: return WinConsoleColors::Purple;
		case Backcolors::Dark_Cyan: return WinConsoleColors::Aqua;
		case Backcolors::Dark_White: return WinConsoleColors::White;
		case Backcolors::Black: return WinConsoleColors::Gray;
		case Backcolors::Red: return WinConsoleColors::LightRed;
		case Backcolors::Green: return WinConsoleColors::LightGreen;
		case Backcolors::Yellow: return WinConsoleColors::LightYellow;
		case Backcolors::Blue: return WinConsoleColors::LightBlue;
		case Backcolors::Magenta: return WinConsoleColors::LightPurple;
		case Backcolors::Cyan: return WinConsoleColors::LightAqua;
		case AnsiStyle::Backcolors::White:
		default: return WinConsoleColors::BrightWhite;
	}
}

void Console::SetForegroundColor(Forecolors color) noexcept
{
	WinConsoleColors consoleColor = AnsiForegroundToWinColor(color);
	SetConsoleTextAttribute(hConsole, (int)consoleColor);
}

void Console::SetBackgroundColor(Backcolors color) noexcept
{
	WinConsoleColors consoleColor = WinConsoleColors::White;
	SetConsoleTextAttribute(hConsole, 16 * (int)consoleColor);
}

void Console::Reset() noexcept
{
	SetConsoleTextAttribute(hConsole, baseConsoleInfo.wAttributes);
}

void Console::Clear() noexcept
{
	COORD cursorPos = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	DWORD written, cells = consoleInfo.dwSize.X * consoleInfo.dwSize.Y;
	FillConsoleOutputCharacterW(hConsole, ' ', cells, cursorPos, &written);
	FillConsoleOutputAttribute(hConsole, consoleInfo.wAttributes, cells, cursorPos, &written);
	SetConsoleCursorPosition(hConsole, cursorPos);;
}

std::size_t Console::GetWidth() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	return consoleInfo.dwSize.X;
}

std::size_t Console::GetHeight() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	return consoleInfo.dwSize.Y;
}

std::pair<std::size_t, std::size_t> Console::GetSize() noexcept
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	return { consoleInfo.dwSize.X, consoleInfo.dwSize.Y };
}

#endif

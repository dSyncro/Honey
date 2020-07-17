#include "../Console.h"

#ifndef HNYPT_WINDOWS

#include <sys/ioctl.h>
#include <unistd.h>

void Console::SetForegroundColor(AnsiStyle::Forecolors color) noexcept { std::cout << color; }
void Console::SetBackgroundColor(AnsiStyle::Backcolors color) noexcept { std::cout << color; }
void Console::Reset() noexcept { std::cout << AnsiStyle::Reset; }
void Console::Clear() noexcept { std::cout << AnsiStyle::Clear << AnsiStyle::CursorNavigation::Home; }

std::size_t Console::GetWidth() noexcept
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size.ws_col;
}

std::size_t Console::GetHeight() noexcept
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size.ws_row;
}

std::pair<std::size_t, std::size_t> Console::GetSize() noexcept
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return { size.ws_col, size.ws_row };
}

#endif
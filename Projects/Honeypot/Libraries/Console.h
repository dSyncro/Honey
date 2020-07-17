#pragma once

#define HNYPT_WINDOWS
#if defined(HNYPT_WINDOWS)
#	include <Windows.h>
#endif

#include <iomanip>

#include "AnsiStyle.h"

class Console {

public:

	enum class Alignment {
		Left = 0,
		Right = 1,
	};

	struct AlignmentInfo {

		AlignmentInfo(std::size_t width = 0, char fill = ' ', Alignment method = Alignment::Left)
			: Width(width), Fill(fill), Method(method) {}

		std::size_t Width;
		char Fill;
		Alignment Method;

	};

	Console() = delete;

	static void NewLine() noexcept { std::cout << '\n'; }

	static void SetForegroundColor(AnsiStyle::Forecolors color) noexcept;
	static void SetBackgroundColor(AnsiStyle::Backcolors color) noexcept;

	static void Reset() noexcept;
	static void Clear() noexcept;

	static std::size_t GetWidth() noexcept;
	static std::size_t GetHeight() noexcept;
	static std::pair<std::size_t, std::size_t> GetSize() noexcept;

	template  <typename... Args>
	static void Align(const AlignmentInfo& info, Args... args) noexcept
	{
		std::ios state = std::ios(nullptr);
		state.copyfmt(std::cout);

		switch (info.Method)
		{
			case Alignment::Left: std::cout << std::left; break;
			case Alignment::Right: std::cout << std::right; break;
		}

		std::cout << std::setw(info.Width) << std::setfill(info.Fill);
		Write(args...);

		std::cout.copyfmt(state);
	}

	template <typename... Args>
	static void Alert(Args... args) noexcept
	{
		SetForegroundColor(AnsiStyle::Forecolors::Yellow);
		WriteLine(args...);
		Reset();
	}

	template <typename... Args>
	static void Error(Args... args) noexcept
	{
		SetForegroundColor(AnsiStyle::Forecolors::Red);
		(std::cerr << ... << args) << '\n';
		Reset();
	}

	template <typename... Args>
	static void Write(Args... args)
	{
		(std::cout << ... << args);
	}

	template <typename... Args>
	static void WriteColored(AnsiStyle::Forecolors color, Args... args) noexcept
	{
		SetForegroundColor(color);
		Write(args...);
		Reset();
	}

	template <typename... Args>
	static void WriteLine(Args... args) noexcept
	{
		(std::cout << ... << args) << '\n';
	}

	template <typename... Args>
	static void WriteColoredLine(AnsiStyle::Forecolors color, Args... args) noexcept
	{
		SetForegroundColor(color);
		WriteLine(args...);
		Reset();
	}

};
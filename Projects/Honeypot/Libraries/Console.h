#pragma once

#define HNYPT_WINDOWS
#if defined(HNYPT_WINDOWS)
#	include <Windows.h>
#endif

#include <iomanip>

#include "AnsiStyle.h"

namespace Console {

	enum class Alignment {
		Left = 0,
		Right = 1
	};

	struct AlignmentInfo {

		AlignmentInfo(long long width = 0, char fill = ' ', Alignment method = Alignment::Left) 
			: Width(width), Fill(fill), Method(method) {}

		long long Width;
		char Fill;
		Alignment Method;

	};

	inline void NewLine() noexcept { std::cout << '\n'; }

	void SetForegroundColor(AnsiStyle::Forecolors color) noexcept;
	void SetBackgroundColor(AnsiStyle::Backcolors color) noexcept;

	void Reset() noexcept;
	void Clear() noexcept;

	template  <typename... Args>
	void Align(const AlignmentInfo& info, Args... args) noexcept
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
	void Alert(Args... args) noexcept
	{
		SetForegroundColor(AnsiStyle::Forecolors::Yellow);
		WriteLine(args...);
		Reset();
	}

	template <typename... Args>
	void Error(Args... args) noexcept
	{
		SetForegroundColor(AnsiStyle::Forecolors::Red);
		(std::cerr << ... << args) << '\n';
		Reset();
	}

	template <typename... Args>
	void Write(Args... args)
	{
		(std::cout << ... << args);
	}

	template <typename... Args>
	void WriteColored(AnsiStyle::Forecolors color, Args... args) noexcept
	{
		SetForegroundColor(color);
		Write(args...);
		Reset();
	}

	template <typename... Args>
	void WriteLine(Args... args) noexcept
	{
		(std::cout << ... << args) << '\n';
	}

	template <typename... Args>
	void WriteColoredLine(AnsiStyle::Forecolors color, Args... args) noexcept
	{
		SetForegroundColor(color);
		WriteLine(args...);
		Reset();
	}
}
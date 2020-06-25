#include "ArgumentParser.h"

#include "Exceptions.h"
#include "../Libraries/Console.h"

ArgumentParser::ArgumentParser(int argc, char** argv) 
	: _argc(argc), _argv(argv)
{
	_current = Current();
}

ArgumentParser::~ArgumentParser()
{
	Deallocate();
}

void ArgumentParser::AddPositionalArgument(const Argument& argument)
{
	_positionalArguments.push_back(std::make_pair(argument, nullptr));
}

void ArgumentParser::AddToggle(const Toggle& flag)
{
	_toggles.push_back(std::make_pair(flag, false));
}

void ArgumentParser::AddFlag(const Flag& flag)
{
	_flags.push_back(std::make_pair(flag, nullptr));
}

std::string* ArgumentParser::GetPositionalValueByName(const std::string& name)
{
	for (const auto& [argument, values] : _positionalArguments)
		if (argument.Name == name) return values;
	return nullptr;
}

bool ArgumentParser::GetToggleValueByName(const std::string& command)
{
	for (const auto& [toggle, value] : _toggles)
		if (toggle.CommandName == command) return value;
	return false;
}

bool ArgumentParser::GetToggleValueByAlias(const std::string& alias)
{
	for (const auto& [toggle, value] : _toggles)
		if (toggle.CommandAlias == alias) return value;
	return false;
}

std::string* ArgumentParser::GetFlagValueByName(const std::string& command)
{
	for (const auto& [flag, values] : _flags)
		if (flag.CommandName == command) return values;
	return nullptr;
}

std::string* ArgumentParser::GetFlagValueByAlias(const std::string& alias)
{
	for (const auto& [flag, values] : _flags)
		if (flag.CommandAlias == alias) return values;
	return false;
}

void ArgumentParser::Parse()
{
	while (_tokenIndex < _argc)
	{
		// Is flag?
		if (IsCurrentFlag())
			ParseFlag();
		else ParsePositional();
	}

	Validate();
}

void ArgumentParser::PrintHelp()
{
	if (_positionalArguments.size() > 0) PrintPositionalArgumentsHelp();
	if (_toggles.size() > 0) PrintTogglesHelp();
	if (_flags.size() > 0) PrintFlagsHelp();
}

void ArgumentParser::PrintPositionalArgumentsHelp()
{
	const unsigned int hLength = 16 + // Name
		8 + // Nargs
		64 + // Description
		10; // Required

	std::string header = "Positional Arguments";
	std::string padding = std::string((hLength - header.length() - 2) / 2, ' ');
	Console::WriteLine(AnsiStyle::Decorations::Reversed, "|", padding, header, padding, "|", AnsiStyle::Reset);

	Console::Align(Console::AlignmentInfo(16), "Name");
	Console::Align(Console::AlignmentInfo(8), "N.Args");
	Console::Align(Console::AlignmentInfo(64), "Description");
	Console::Align(Console::AlignmentInfo(10), "Required?");
	Console::WriteLine();

	Console::Align(Console::AlignmentInfo(hLength), std::string(hLength, '-'));
	Console::WriteLine();

	for (const auto& [argument, _] : _positionalArguments)
	{
		Console::Align(Console::AlignmentInfo(16), argument.Name);
		Console::Align(Console::AlignmentInfo(8), argument.NumberOfArguments);
		Console::Align(Console::AlignmentInfo(64), argument.Description);
		if (argument.IsRequired) 
			Console::WriteColored(AnsiStyle::Forecolors::Yellow, "[Required]");
		Console::WriteLine();
	}

	Console::WriteLine();
}

void ArgumentParser::PrintTogglesHelp()
{
	const unsigned int hLength = 8 + // Name
		16 + // Alias
		64 + // Description
		10; // Required

	std::string header = "Toggling Flags";
	std::string padding = std::string((hLength - header.length() - 2) / 2, ' ');
	Console::WriteLine(AnsiStyle::Decorations::Reversed, "|", padding, header, padding, "|", AnsiStyle::Reset);

	Console::Align(Console::AlignmentInfo(8), "Name");
	Console::Align(Console::AlignmentInfo(16), "Alias");
	Console::Align(Console::AlignmentInfo(64), "Description");
	Console::Align(Console::AlignmentInfo(10), "Required?");
	Console::WriteLine();

	Console::Align(Console::AlignmentInfo(hLength), std::string(hLength, '-'));
	Console::WriteLine();

	for (const auto& [toggle, _] : _toggles)
	{
		Console::Align(Console::AlignmentInfo(8), toggle.CommandName);
		Console::Align(Console::AlignmentInfo(16), toggle.CommandAlias);
		Console::Align(Console::AlignmentInfo(64), toggle.Description);
		if (toggle.IsRequired)
			Console::WriteColored(AnsiStyle::Forecolors::Yellow, "[Required]");
		Console::WriteLine();
	}

	Console::WriteLine();
}

void ArgumentParser::PrintFlagsHelp()
{
	const unsigned int hLength = 8 + // Name
		16 + // Alias
		8 + // Nargs
		56 + // Description
		10; // Required

	std::string header = "Value Flags";
	std::string padding = std::string((hLength - header.length() - 2) / 2, ' ');
	Console::WriteLine(AnsiStyle::Decorations::Reversed, "|", padding, header, padding, "|", AnsiStyle::Reset);

	Console::Align(Console::AlignmentInfo(8), "Name");
	Console::Align(Console::AlignmentInfo(16), "Alias");
	Console::Align(Console::AlignmentInfo(8), "N.Args");
	Console::Align(Console::AlignmentInfo(56), "Description");
	Console::Align(Console::AlignmentInfo(10), "Required?");
	Console::WriteLine();

	Console::Align(Console::AlignmentInfo(hLength), std::string(hLength, '-'));
	Console::WriteLine();

	for (const auto& [flag, _] : _flags)
	{
		Console::Align(Console::AlignmentInfo(8), flag.CommandName);
		Console::Align(Console::AlignmentInfo(16), flag.CommandAlias);
		Console::Align(Console::AlignmentInfo(8), flag.NumberOfArguments);
		Console::Align(Console::AlignmentInfo(56), flag.Description);
		if (flag.IsRequired)
			Console::WriteColored(AnsiStyle::Forecolors::Yellow, "[Required]");
		Console::WriteLine();
	}

	Console::WriteLine();
}

ArgumentParser& ArgumentParser::operator =(const ArgumentParser& other)
{
	Deallocate();
	std::memcpy(this, &other, sizeof(ArgumentParser));
	return *this;
}

void ArgumentParser::Reset()
{
	Deallocate();

	_positionalArguments.clear();
	_toggles.clear();
	_flags.clear();

	_positionalIndex = 0;
	_tokenIndex = 1;
}

void ArgumentParser::Deallocate()
{
	for (const auto& [_, values] : _positionalArguments)
		delete[] values;

	for (const auto& [_, values] : _flags)
		delete[] values;
}

void ArgumentParser::Validate()
{
	for (const auto& [argument, values] : _positionalArguments)
		 if (argument.IsRequired && values == nullptr) 
			 throw ArgumentRequiredException(argument.Name);

	for (const auto& [flag, values] : _flags)
		if (flag.IsRequired && values == nullptr) 
			throw ArgumentRequiredException(flag.CommandName);
}

void ArgumentParser::ParsePositional()
{
	if (_positionalIndex >= _positionalArguments.size())
		throw TooManyArgumentsException("[Positional Arguments]");

	const Argument& argument = _positionalArguments[_positionalIndex].first;
	std::string* values = _positionalArguments[_positionalIndex].second;

	values = new std::string[argument.NumberOfArguments];

	for (int i = 0; i < argument.NumberOfArguments; i++)
	{
		if (IsCurrentFlag() || IsCurrentNull()) 
			throw InsufficientArgumentsProvidedException(argument.Name);

		values[i] = _current;
		Step();
	}

	_positionalIndex++;
}

void ArgumentParser::ParseFlag()
{
	std::size_t length = _current.length();

	if (length < 2) return;

	if (IsCurrentAlias()) ParseAliasFlag();
	else ParseCommandFlag();

	Step();
}

void ArgumentParser::ParseAliasFlag()
{
	const char* alias = _current.c_str() + 2;

	for (auto& [toggle, value] : _toggles)
	{
		if (toggle.CommandAlias != alias) continue;
		value = true;
		return;
	}

	for (auto& [flag, values] : _flags)
	{
		if (flag.CommandAlias != alias) continue;

		values = new std::string[flag.NumberOfArguments];
		for (int i = 0; i < flag.NumberOfArguments; i++)
		{
			Step();

			if (IsCurrentFlag() || IsCurrentNull())
				throw InsufficientArgumentsProvidedException(flag.CommandName);

			values[i] = _current;
		}
		return;
	}
}

void ArgumentParser::ParseCommandFlag()
{
	const char* name = _current.c_str() + 1;

	for (auto& [toggle, value] : _toggles)
	{
		if (toggle.CommandName != name) continue;
		value = true;
	}

	for (auto& [flag, values] : _flags)
	{
		if (flag.CommandName != name) continue;

		values = new std::string[flag.NumberOfArguments];
		for (int i = 0; i < flag.NumberOfArguments; i++)
		{
			Step();

			if (IsCurrentFlag() || IsCurrentNull())
				throw InsufficientArgumentsProvidedException(flag.CommandName);

			values[i] = _current;
		}
		return;
	}
}

std::string ArgumentParser::Peek(unsigned int offset)
{
	unsigned int index = _tokenIndex + offset;
	if (index >= _argc) return "";
	return _argv[index];
}
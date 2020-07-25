#include "ArgumentParser.h"

#include<filesystem>

#include "Exceptions.h"
#include "../Libraries/Console.h"

std::string NargsToString(int nargs)
{
	switch (nargs)
	{
		case Argument::ZEROORMORE: return "*";
		case Argument::ONEORMORE: return "+";
		default: return std::to_string(nargs);
	}
}

ArgumentParser::ArgumentParser(std::size_t argumentsCount, char** arguments)
	: _argc(argumentsCount), _argv(arguments)
{
	_current = Current();
}

void ArgumentParser::AddPositionalArgument(const Argument& argument)
{
	_positionalArguments.push_back(std::make_pair(argument, StringList()));
}

void ArgumentParser::AddToggle(const Toggle& flag)
{
	_toggles.push_back(std::make_pair(flag, false));
}

void ArgumentParser::AddFlag(const Flag& flag)
{
	_flags.push_back(std::make_pair(flag, StringList()));
}

const ArgumentParser::StringList& ArgumentParser::GetPositionalValueByName(const std::string& name)
{
	for (const auto& [argument, values] : _positionalArguments)
		if (argument.Name == name) return values;
	return StringList();
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

const ArgumentParser::StringList& ArgumentParser::GetFlagValueByName(const std::string& command)
{
	for (const auto& [flag, values] : _flags)
		if (flag.CommandName == command) return values;
	return StringList();
}

const ArgumentParser::StringList& ArgumentParser::GetFlagValueByAlias(const std::string& alias)
{
	for (const auto& [flag, values] : _flags)
		if (flag.CommandAlias == alias) return values;
	return StringList();
}

void ArgumentParser::Parse()
{
	Reset();

	while (_tokenIndex < _argc)
	{
		if (IsCurrentFlag()) ParseFlag();
		else ParsePositional();
	}

	Validate();
}

void ArgumentParser::PrintHelp()
{
	Console::Write("Syntax: ", _argv[0], " ");
	
	for (const auto& [argument, _] : _positionalArguments)
	{
		if (argument.NumberOfArguments != 1)
		{
			if (argument.IsRequired)
				Console::Write("{", argument.Name, "} ");
			else Console::Write("[{", argument.Name, "}] ");

			continue;
		}

		if (argument.IsRequired)
			Console::Write(argument.Name, " ");
		else Console::Write("[", argument.Name, "] ");
	}

	for (const auto& [flag, _] : _flags)
	{
		if (flag.IsRequired)
			Console::Write(flag.CommandName, " {", NargsToString(flag.NumberOfArguments), "} ");
		else
			Console::Write("[", flag.CommandName, " {", NargsToString(flag.NumberOfArguments), "}] ");
	}

	Console::NewLine();
	Console::NewLine();

	if (_positionalArguments.size() > 0) PrintPositionalArgumentsHelp();
	if (_toggles.size() > 0) PrintTogglesHelp();
	if (_flags.size() > 0) PrintFlagsHelp();
}

void ArgumentParser::PrintDescription(const std::string& description, std::size_t availableSpace, std::size_t newLinePadding)
{
	std::size_t offset;
	std::size_t descriptionLength = description.length();
	for (offset = 0; descriptionLength > availableSpace; offset += availableSpace)
	{
		Console::WriteLine(description.substr(offset, availableSpace));
		descriptionLength -= availableSpace,
		Console::Fill(newLinePadding);
	}

	Console::Write(description.substr(offset, descriptionLength));
}

void ArgumentParser::PrintPositionalArgumentsHelp()
{
	const std::size_t hLength = 16 + // Name
		8 + // Alias
		64; // Description

	std::string header = "Positional Arguments";
	std::string padding = std::string((hLength - header.length() - 2) / 2, ' ');
	Console::WriteLine(AnsiStyle::Decorations::Reversed, "|", padding, header, padding, "|", AnsiStyle::Reset);

	Console::Align(Console::AlignmentInfo(16), "Name");
	Console::Align(Console::AlignmentInfo(8), "N.Args");
	Console::Align(Console::AlignmentInfo(64), "Description");
	Console::WriteLine();

	Console::Align(Console::AlignmentInfo(hLength), std::string(hLength, '-'));
	Console::WriteLine();

	for (const auto& [argument, _] : _positionalArguments)
	{
		Console::Align(Console::AlignmentInfo(16), argument.Name);
		std::string nargs = NargsToString(argument.NumberOfArguments);
		Console::Align(Console::AlignmentInfo(8), nargs);
		PrintDescription(argument.Description, 64, 16 + 8);
		Console::NewLine();
	}

	Console::NewLine();
}

void ArgumentParser::PrintTogglesHelp()
{
	const std::size_t hLength = 8 + // Name
		16 + // Alias
		64; // Description

	std::string header = "Toggling Flags";
	std::string padding = std::string((hLength - header.length() - 2) / 2, ' ');
	Console::WriteLine(AnsiStyle::Decorations::Reversed, "|", padding, header, padding, "|", AnsiStyle::Reset);

	Console::Align(Console::AlignmentInfo(8), "Option");
	Console::Align(Console::AlignmentInfo(16), "Extended");
	Console::Align(Console::AlignmentInfo(64), "Description");
	Console::WriteLine();

	Console::Align(Console::AlignmentInfo(hLength), std::string(hLength, '-'));
	Console::WriteLine();

	for (const auto& [toggle, _] : _toggles)
	{
		Console::Align(Console::AlignmentInfo(8), "-" + toggle.CommandName);
		Console::Align(Console::AlignmentInfo(16), "--" + toggle.CommandAlias);
		PrintDescription(toggle.Description, 64, 8 + 16);
		Console::NewLine();
	}

	Console::NewLine();
}

void ArgumentParser::PrintFlagsHelp()
{
	const std::size_t hLength = 8 + // Name
		16 + // Alias
		8 + // Nargs
		56; // Description

	std::string header = "Value Flags";
	std::string padding = std::string((hLength - header.length() - 2) / 2, ' ');
	Console::WriteLine(AnsiStyle::Decorations::Reversed, "|", padding, header, padding, "|", AnsiStyle::Reset);

	Console::Align(Console::AlignmentInfo(8), "Name");
	Console::Align(Console::AlignmentInfo(16), "Alias");
	Console::Align(Console::AlignmentInfo(8), "N.Args");
	Console::Align(Console::AlignmentInfo(56), "Description");
	Console::WriteLine();

	Console::Align(Console::AlignmentInfo(hLength), std::string(hLength, '-'));
	Console::WriteLine();

	for (const auto& [flag, _] : _flags)
	{
		Console::Align(Console::AlignmentInfo(8), "-" + flag.CommandName);
		Console::Align(Console::AlignmentInfo(16), "--" + flag.CommandAlias);
		std::string nargs = NargsToString(flag.NumberOfArguments);
		Console::Align(Console::AlignmentInfo(8), nargs);
		PrintDescription(flag.Description, 56, 8 + 16 + 8);
		Console::NewLine();
	}

	Console::WriteLine();
}

ArgumentParser& ArgumentParser::operator =(const ArgumentParser& other)
{
	std::memcpy(this, &other, sizeof(ArgumentParser));
	return *this;
}

void ArgumentParser::Reset()
{
	for (auto& [_, values] : _positionalArguments)
		values = StringList();

	for (auto& [_, value] : _toggles)
		value = false;

	for (auto& [_, values] : _flags)
		values = StringList();

	_positionalIndex = 0;
	_tokenIndex = 1;
}

void ArgumentParser::Clear()
{
	_positionalArguments.clear();
	_toggles.clear();
	_flags.clear();
}

void ArgumentParser::ResetAndClear()
{
	Reset();
	Clear();
}

void ArgumentParser::Validate()
{
	for (const auto& [argument, values] : _positionalArguments)
		 if (argument.IsRequired && values.size()) 
			 throw ArgumentRequiredException(argument.Name);

	for (const auto& [flag, values] : _flags)
		if (flag.IsRequired && values.size()) 
			throw ArgumentRequiredException(flag.CommandName);
}

void ArgumentParser::ParsePositional()
{
	if (_positionalIndex >= _positionalArguments.size())
		throw TooManyArgumentsException("[Positional Arguments]");

	auto& [argument, valueArray] = _positionalArguments[_positionalIndex];

	switch (argument.NumberOfArguments)
	{
		case Argument::ZEROORMORE: 
		{
			ParseZeroOrMore(valueArray);
			break;
		}

		case Argument::ONEORMORE: 
		{
			bool succeded = ParseOneOrMore(valueArray);
			if (!succeded) throw InsufficientArgumentsProvidedException(argument.Name);
			break;
		}
			
		default: 
		{
			bool succeded = ParseArguments(valueArray, argument.NumberOfArguments);
			if (!succeded) throw InsufficientArgumentsProvidedException(argument.Name);
			break;
		}
	}
	_positionalIndex++;
}

void ArgumentParser::ParseFlag()
{
	std::size_t length = _current.length();

	if (length < 2) return;

	if (IsCurrentAlias()) ParseAliasFlag();
	else ParseCommandFlag();
}

void ArgumentParser::ParseAliasFlag()
{
	// Get command alias
	const char* alias = _current.c_str() + 2;

	// Try to set a toggle
	for (auto& [toggle, value] : _toggles)
	{
		if (toggle.CommandAlias != alias) continue;
		value = true; Step(); return;
	}

	// Try parse a flag
	for (auto& [flag, valueArray] : _flags)
	{
		if (flag.CommandAlias != alias) continue;

		// It is a flag
		Step(); // Start parsing from the next element

		switch (flag.NumberOfArguments)
		{
			case Flag::ZEROORMORE:
			{
				ParseZeroOrMore(valueArray);
				return;
			}

			case Flag::ONEORMORE:
			{
				bool succeded = ParseOneOrMore(valueArray);
				if (!succeded) throw InsufficientArgumentsProvidedException(alias);
				return;
			}

			default:
			{
				bool succeded = ParseArguments(valueArray, flag.NumberOfArguments);
				if (!succeded) throw InsufficientArgumentsProvidedException(alias);
				return;
			}

		}

	}

	// Unknown flag, maybe it does not exist
	throw UnknownFlagException(alias);
}

void ArgumentParser::ParseCommandFlag()
{
	// Get command name
	const char* name = _current.c_str() + 1;

	// Try to set a toggle
	for (auto& [toggle, value] : _toggles)
	{
		if (toggle.CommandName != name) continue;
		value = true; Step(); return;
	}

	// Try parse a flag
	for (auto& [flag, valueArray] : _flags)
	{
		if (flag.CommandName != name) continue;

		// It is a flag
		Step(); // Start parsing from the next element

		switch (flag.NumberOfArguments)
		{
			case Flag::ZEROORMORE:
			{
				ParseZeroOrMore(valueArray);
				return;
			}

			case Flag::ONEORMORE:
			{
				bool succeded = ParseOneOrMore(valueArray);
				if (!succeded) throw InsufficientArgumentsProvidedException(name);
				return;
			}

			default:
			{
				bool succeded = ParseArguments(valueArray, flag.NumberOfArguments);
				if (!succeded) throw InsufficientArgumentsProvidedException(name);
				return;
			}

		}

	}

	// Unknown flag, maybe it does not exist
	throw UnknownFlagException(name);
}

void ArgumentParser::ParseZeroOrMore(StringList& valueArray)
{
	while (!(IsCurrentFlag() || IsCurrentNull()))
	{
		valueArray.push_back(_current);
		Step();
	}
}

bool ArgumentParser::ParseOneOrMore(StringList& valueArray)
{
	while (!(IsCurrentFlag() || IsCurrentNull()))
	{
		valueArray.push_back(_current);
		Step();
	}
	return valueArray.size() ? true : false;
}

bool ArgumentParser::ParseArguments(StringList& valueArray, std::size_t nargs)
{
	valueArray.reserve(nargs);
	for (std::size_t i = 0; i < nargs; i++)
	{
		if (IsCurrentFlag() || IsCurrentNull()) return false;

		valueArray[i] = _current;
		Step();
	}

	return true;
}

std::string ArgumentParser::Peek(std::size_t offset)
{
	std::size_t index = _tokenIndex + offset;
	if (index >= _argc) return "";
	return _argv[index];
}
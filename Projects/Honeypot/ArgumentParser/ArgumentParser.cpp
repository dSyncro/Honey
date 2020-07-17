#include "ArgumentParser.h"

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
	Console::Write("Usage: ", _argv[0], " ");
	
	for (const auto& [argument, _] : _positionalArguments)
		if (argument.IsRequired) Console::Write(argument.Name, " ");

	for (const auto& [flag, _] : _flags)
		if (flag.IsRequired) Console::Write(flag.CommandName, " ");

	Console::WriteLine("[Optional]");
	Console::WriteLine();

	if (_positionalArguments.size() > 0) PrintPositionalArgumentsHelp();
	if (_toggles.size() > 0) PrintTogglesHelp();
	if (_flags.size() > 0) PrintFlagsHelp();
}

void ArgumentParser::PrintPositionalArgumentsHelp()
{
	const std::size_t hLength = 16 + // Name
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
		std::string nargs = NargsToString(argument.NumberOfArguments);
		Console::Align(Console::AlignmentInfo(8), nargs);
		Console::Align(Console::AlignmentInfo(64), argument.Description);
		if (argument.IsRequired) 
			Console::WriteColored(AnsiStyle::Forecolors::Yellow, "[Required]");
		Console::WriteLine();
	}

	Console::WriteLine();
}

void ArgumentParser::PrintTogglesHelp()
{
	const std::size_t hLength = 8 + // Name
		16 + // Alias
		64; // Description

	std::string header = "Toggling Flags";
	std::string padding = std::string((hLength - header.length() - 2) / 2, ' ');
	Console::WriteLine(AnsiStyle::Decorations::Reversed, "|", padding, header, padding, "|", AnsiStyle::Reset);

	Console::Align(Console::AlignmentInfo(8), "Name");
	Console::Align(Console::AlignmentInfo(16), "Alias");
	Console::Align(Console::AlignmentInfo(64), "Description");
	Console::WriteLine();

	Console::Align(Console::AlignmentInfo(hLength), std::string(hLength, '-'));
	Console::WriteLine();

	for (const auto& [toggle, _] : _toggles)
	{
		Console::Align(Console::AlignmentInfo(8), "-" + toggle.CommandName);
		Console::Align(Console::AlignmentInfo(16), "--" + toggle.CommandAlias);
		Console::Align(Console::AlignmentInfo(64), toggle.Description);
		Console::WriteLine();
	}

	Console::WriteLine();
}

void ArgumentParser::PrintFlagsHelp()
{
	const std::size_t hLength = 8 + // Name
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
		Console::Align(Console::AlignmentInfo(8), "-" + flag.CommandName);
		Console::Align(Console::AlignmentInfo(16), "--" + flag.CommandAlias);
		std::string nargs = NargsToString(flag.NumberOfArguments);
		Console::Align(Console::AlignmentInfo(8), nargs);
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

	for (auto& [_, values] : _positionalArguments)
		values = nullptr;

	for (auto& [_, value] : _toggles)
		value = false;

	for (auto& [_, values] : _flags)
		values = nullptr;

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

	auto& [argument, values] = _positionalArguments[_positionalIndex];
	switch (argument.NumberOfArguments)
	{
		case Argument::ZEROORMORE: 
		{
			ParseZeroOrMore(values);
			break;
		}

		case Argument::ONEORMORE: 
		{
			bool succeded = ParseOneOrMore(values);
			if (!succeded) throw InsufficientArgumentsProvidedException(argument.Name);
			break;
		}
			
		default: 
		{
			bool succeded = ParseArguments(values, argument.NumberOfArguments);
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
	const char* alias = _current.c_str() + 2;

	for (auto& [toggle, value] : _toggles)
	{
		if (toggle.CommandAlias != alias) continue;
		value = true;
		Step();
		return;
	}

	for (auto& [flag, values] : _flags)
	{
		if (flag.CommandAlias != alias) continue;

		Step();
		values = new std::string[flag.NumberOfArguments];
		for (std::size_t i = 0; i < flag.NumberOfArguments; i++)
		{
			if (IsCurrentFlag() || IsCurrentNull())
				throw InsufficientArgumentsProvidedException(flag.CommandName);

			values[i] = _current;
			Step();
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
		value = true; Step(); return;
	}

	for (auto& [flag, values] : _flags)
	{
		if (flag.CommandName != name) continue;

		Step();
		switch (flag.NumberOfArguments)
		{
			case Flag::ZEROORMORE:
			{
				ParseZeroOrMore(values);
				return;
			}

			case Flag::ONEORMORE:
			{
				bool succeded = ParseOneOrMore(values);
				if (!succeded) throw InsufficientArgumentsProvidedException(name);
				return;
			}

			default:
			{
				bool succeded = ParseArguments(values, flag.NumberOfArguments);
				if (!succeded) throw InsufficientArgumentsProvidedException(name);
				return;
			}

		}

	}

	throw UnknownFlagException(name);
}

void ArgumentParser::ParseZeroOrMore(std::string*& values)
{
	std::vector<std::string> valuesVector;

	while (!(IsCurrentFlag() || IsCurrentNull()))
	{
		valuesVector.push_back(_current);
		Step();
	}

	std::size_t length = valuesVector.size();

	values = new std::string[length];
	for (std::size_t i = 0; i < length; i++)
		values[i] = valuesVector[i];
}

bool ArgumentParser::ParseOneOrMore(std::string*& values)
{
	std::vector<std::string> valuesVector;

	while (!(IsCurrentFlag() || IsCurrentNull()))
	{
		valuesVector.push_back(_current);
		Step();
	}

	std::size_t length = valuesVector.size();

	values = new std::string[length];

	if (!length) return false;

	for (std::size_t i = 0; i < length; i++)
		values[i] = valuesVector[i];

	return true;
}

bool ArgumentParser::ParseArguments(std::string*& values, std::size_t nargs)
{
	values = new std::string[nargs];
	for (std::size_t i = 0; i < nargs; i++)
	{
		if (IsCurrentFlag() || IsCurrentNull()) return false;

		values[i] = _current;
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
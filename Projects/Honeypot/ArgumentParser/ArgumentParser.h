#pragma once

#include <map>
#include <vector>

#include "Flag.h"
#include "Toggle.h"

class ArgumentParser {

private:

	using StringList = std::vector<std::string>;
	using PositionalArgumentsList = std::vector<std::pair<Argument, StringList>>;
	using TogglesList = std::vector<std::pair<Toggle, bool>>;
	using FlagsList = std::vector<std::pair<Flag, std::vector<std::string>>>;

public:

	ArgumentParser(std::size_t argumentsCount, char** arguments);

	void AddPositionalArgument(const Argument& argument);
	void AddToggle(const Toggle& toggle);
	void AddFlag(const Flag& flag);

	const StringList& GetPositionalValueByName(const std::string& name);
	bool GetToggleValueByName(const std::string& command);
	bool GetToggleValueByAlias(const std::string& alias);
	const StringList& GetFlagValueByName(const std::string& command);
	const StringList& GetFlagValueByAlias(const std::string& alias);

	void Parse();

	void PrintHelp();

	ArgumentParser& operator =(const ArgumentParser& other);

private:

	void Reset();
	void Clear();
	void ResetAndClear();
	void Validate();

	void ParseFlag();
	void ParseAliasFlag();
	void ParseCommandFlag();
	void ParsePositional();
	void ParseZeroOrMore(StringList& valueArray);
	bool ParseOneOrMore(StringList& valueArray);
	bool ParseArguments(StringList& valueArray, std::size_t nargs);

	void PrintPositionalArgumentsHelp();
	void PrintTogglesHelp();
	void PrintFlagsHelp();

	std::string Current() { return Peek(); }
	std::string Next() { return Peek(1); }
	std::string Peek(std::size_t offset = 0);
	void Step() { _tokenIndex++; _current = Current(); }

	bool IsCurrentNull() { return !_current.length(); }
	bool IsCurrentFlag() { return _current.length() > 0 && _current[0] == _prefixChar; }
	bool IsCurrentAlias() { return IsCurrentFlag() && _current.length() > 1 && _current[1] == _prefixChar; }

	static void PrintDescription(const std::string& description, std::size_t availableSpace, std::size_t newLinePadding = 0);

	PositionalArgumentsList _positionalArguments;
	TogglesList _toggles;
	FlagsList _flags;

	char _prefixChar = '-';

	std::size_t _positionalIndex = 0;
	std::size_t _tokenIndex = 1;

	std::string _current = "";

	std::size_t _argc;
	char** _argv;

};
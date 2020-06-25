#pragma once

#include <map>
#include <vector>

#include "Flag.h"
#include "Toggle.h"

class ArgumentParser {

public:

	ArgumentParser(int argc, char** argv);
	~ArgumentParser();

	void AddPositionalArgument(const Argument& argument);
	void AddToggle(const Toggle& toggle);
	void AddFlag(const Flag& flag);

	std::string* GetPositionalValueByName(const std::string& name);
	bool GetToggleValueByName(const std::string& command);
	bool GetToggleValueByAlias(const std::string& alias);
	std::string* GetFlagValueByName(const std::string& command);
	std::string* GetFlagValueByAlias(const std::string& alias);

	void Parse();

	void PrintHelp();

	ArgumentParser& operator =(const ArgumentParser& other);

private:

	void Reset();
	void Deallocate();
	void Validate();

	void ParseFlag();
	void ParseAliasFlag();
	void ParseCommandFlag();
	void ParsePositional();

	void PrintPositionalArgumentsHelp();
	void PrintTogglesHelp();
	void PrintFlagsHelp();

	std::string Current() { return Peek(); }
	std::string Next() { return Peek(1); }
	std::string Peek(unsigned int offset = 0);
	void Step() { _tokenIndex++; _current = Current(); }

	bool IsCurrentNull() { return !_current.length(); }
	bool IsCurrentFlag() { return _current.length() > 0 && _current[0] == _prefixChar; }
	bool IsCurrentAlias() { return IsCurrentFlag() && _current.length() > 1 && _current[1] == _prefixChar; }

	using PositionalArgumentsList = std::vector<std::pair<Argument, std::string*>>;
	using TogglesList = std::vector<std::pair<Toggle, bool>>;
	using FlagsList = std::vector<std::pair<Flag, std::string*>>;

	PositionalArgumentsList _positionalArguments;
	TogglesList _toggles;
	FlagsList _flags;

	char _prefixChar = '-';

	unsigned int _positionalIndex = 0;
	unsigned int _tokenIndex = 1;

	std::string _current = "";

	int _argc;
	char** _argv;

};
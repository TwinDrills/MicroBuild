/*
MicroBuild
Copyright (C) 2016 TwinDrills

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "Core/Platform/Path.h"
#include "Core/Config/ConfigTokenizer.h"

namespace MicroBuild {

// A condition that determines if a key exists with the given defines/config.
struct ConfigFileExpression
{
	bool Invert;
	TokenType Operator;
	std::string Value;
	std::vector<ConfigFileExpression> Children;

	ConfigFileExpression()
		: Invert(false)
		, Operator(TokenType::Unknown)
	{
	}
};

// An individual value associated with a key, and its conditionals.
struct ConfigFileValue
{
	std::string Value;
	std::vector<ConfigFileExpression> Conditions;

	// Post resolve values.
	bool HasResolvedValue;
	std::string ResolvedValue;
	bool ConditionResult;

	ConfigFileValue()
		: HasResolvedValue(false)
		, ConditionResult(true)
	{
	}
};

// An individual key.
struct ConfigFileKey
{
	std::string Name;
	std::vector<ConfigFileValue> Values;
};

// An individual group of config keys.
struct ConfigFileGroup
{
	std::string Name;
	std::map<std::string, ConfigFileKey> Keys;
};

// Our base config file class. Implements a simple INI style file format.
class ConfigFile
{
public:
	ConfigFile();
	~ConfigFile();

	// Parses the config file located at the given path and converts in into
	// group and value keys.
	bool Parse(const Platform::Path& path);

	// Copies all the values that exist in another config file into this one.
	void Merge(const ConfigFile& file);

	// Sets or adds the given value to the group with the given name.
	void SetOrAddValue(
		const std::string& group,
		const std::string& key,
		const std::string& value); 

	// Resolves all expression references and evaluates them. It also
	// performs token replacement within values.
	void Resolve();

	// Gets all the values of a given key in the given group.
	std::vector<std::string> GetValues(
		const std::string& group, 
		const std::string& key);

protected:
	void Error(const Token& token, const char* format, ...);

	void UnexpectedToken(const Token& tok);
	void UnexpectedEndOfTokens(const Token& tok);
	void UnexpectedNestedGroup(const Token& tok);

	void PrettyPrintExpression(
		const ConfigFileExpression& expressions, int depth = 0);
	void PrettyPrintExpressions(
		std::vector<ConfigFileExpression>& expressions);

	bool EndOfTokens();
	Token& NextToken();
	Token& PeekToken();
	Token& CurrentToken();
	bool ExpectToken(TokenType type);

	bool ParseExpression(ConfigFileExpression& expression);
	bool ParseExpressionComparison(ConfigFileExpression& expression);
	bool ParseExpressionUnary(ConfigFileExpression& expression);
	bool ParseExpressionFactor(ConfigFileExpression& expression);
	bool ParseStatement();
	bool ParseAssignment();
	bool ParseIf();
	bool ParseGroup();
	bool ParseBlock();

	std::string ReplaceTokens(
		const std::string& value,
		const std::string& baseGroup);

	std::string ResolveTokenReplacement(
		const std::string& key,
		const std::string& group);

private:
	Platform::Path m_path;
	FILE* m_file;

	ConfigTokenizer m_tokenizer;
	int m_tokenIndex;

	std::string m_currentGroup;
	std::map<std::string, ConfigFileGroup> m_groups;

	std::vector<ConfigFileExpression> m_expressionStack;
	
};

}; // namespace MicroBuild
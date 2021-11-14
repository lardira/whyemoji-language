#pragma once

#include <vector>
#include <memory>
#include <map>

#include "ParserNode.h"
#include "WhyToken.h"
#include "Utils.h"

class WhyParser
{
public:
	WhyParser() = default;
	~WhyParser() = default;

	static void Parse(std::vector<WhyToken>& tokens);
public:
	static std::vector<SharedNodePtr> parserNodeTree;

private:
	static bool TryAdvance();
	static int GetNumber();
	static std::string GetString();
	static SharedNodePtr GetFactor();
	static SharedNodePtr GetTerm();
	static SharedNodePtr GetExpression();

	static void AssignToVariable(std::string& name);
	static void MakePrintNode();
private:
	static std::vector<WhyToken> Tokens;
	static std::map<std::string, SharedNodePtr> variables;
	static WhyToken currentToken;
	static int currentTokenID;
};


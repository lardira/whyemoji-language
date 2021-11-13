#pragma once

#include <vector>
#include <typeinfo>
#include <memory>
#include <map>

#include "Utils.h"
#include "WhyToken.h"
#include "ParserNode.h"

class WhyParser
{
public:
	WhyParser() = default;
	~WhyParser() = default;

	static void Parse(std::vector<WhyToken>& tokens);

public:
	static std::vector<SharedNodePtr> parserNodeTree;

private:
	static SharedNodePtr GetFactor();
	static SharedNodePtr GetTerm();
	static SharedNodePtr GetExpression();
	static int GetNumber();
	static std::string GetString();

	static bool TryAdvance();
private:
	static std::vector<WhyToken> Tokens;
	static std::map<std::string, SharedNodePtr> variables;
	static WhyToken currentToken;
	static unsigned int currentTokenID;
};


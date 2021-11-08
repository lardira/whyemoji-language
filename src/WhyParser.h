#pragma once

#include <vector>
#include <typeinfo>

#include "Utils.h"
#include "WhyToken.h"
#include "ParserNode.h"

class WhyParser
{
public:
	WhyParser() = default;
	~WhyParser() = default;

	static void Parse(std::vector<WhyToken>& tokens);

private:
	static ParserNode* GetFactor();
	static ParserNode* GetTerm();
	static ParserNode* GetExpression();
	static int GetNumber();
	static std::string GetString();

	static bool TryAdvance();
private:
	static std::vector<WhyToken> Tokens;
	static WhyToken currentToken;
	static unsigned int currentTokenID;
};


#pragma once

#include <vector>

#include "WhyToken.h"
#include "ParserNode.h"

class WhyParser
{
public:
	WhyParser() = default;
	~WhyParser() = default;

	static void Parse(std::vector<WhyToken>& tokens);
private:
	static NumberNode GetFactor();
	static int GetTerm();
	static int GetExpression();

	static bool TryAdvance();
private:
	static std::vector<WhyToken> Tokens;
	static WhyToken currentToken;
	static unsigned int currentTokenID;
};


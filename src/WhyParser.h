#pragma once

#include <vector>
#include <typeinfo>
#include <memory>

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
	static SharedNodePtr GetFactor();
	static SharedNodePtr GetTerm();
	static SharedNodePtr GetExpression();
	static int GetNumber();
	static std::string GetString();

	static bool TryAdvance();
private:
	static std::vector<WhyToken> Tokens;
	static WhyToken currentToken;
	static unsigned int currentTokenID;


};


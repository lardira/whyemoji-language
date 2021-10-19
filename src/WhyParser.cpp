#include "WhyParser.h"

std::vector<WhyToken> WhyParser::Tokens;
unsigned int WhyParser::currentTokenID;
WhyToken WhyParser::currentToken = {WhyToken::Type::Undefined};

void WhyParser::Parse(std::vector<WhyToken>& tokens)
{
	Tokens = tokens;
	currentTokenID = 0;
	currentToken = Tokens[currentTokenID];
}

NumberNode WhyParser::GetFactor()
{
	int result = 0;
	while (currentToken.GetType() == WhyToken::Type::Integer)
	{
		result = result * 10 + currentToken.GetValue();

		if (TryAdvance() == false)
			break;
	}
	return NumberNode{currentToken};
}

//int WhyParser::GetTerm()
//{
	//TODO: LOOK HOW PARSERS WORK
//}
//
//int WhyParser::GetExpression()
//{
//
//}

bool WhyParser::TryAdvance()
{
	if ((currentTokenID + 1) < Tokens.size())
	{
		currentTokenID++;
		currentToken = Tokens[currentTokenID];
		return true;
	}
	else
		return false;
}

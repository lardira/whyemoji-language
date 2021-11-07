#include "WhyParser.h"

std::vector<WhyToken> WhyParser::Tokens;
unsigned int WhyParser::currentTokenID;
WhyToken WhyParser::currentToken = {WhyToken::Type::Undefined};

void WhyParser::Parse(std::vector<WhyToken>& tokens)
{
	Tokens = tokens;
	currentTokenID = 0;
	currentToken = Tokens[currentTokenID];

	for (int t = 0; t < tokens.size(); t++)
	{
		switch (currentToken.GetType())
		{
			case WhyToken::Type::Integer:
				GetFactor();
				break;
			case WhyToken::Type::OperMinus:
			case WhyToken::Type::OperPlus:
				//GetOperation();
				break;
			default:
				//TODO: throw an error
				break;
		}
	}
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
	return NumberNode{result};
}

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

#include "WhyParser.h"

std::vector<WhyToken> WhyParser::Tokens;
unsigned int WhyParser::currentTokenID;
WhyToken WhyParser::currentToken = {WhyToken::Type::Undefined};

//DEBUG ONLY
static void OutputExpression(ParserNode* expression, std::string prefix = 0)
{
	if (expression != nullptr)
	{
		std::string info =
			typeid(*expression).name() == typeid(StringNode).name() ?
			expression->GetString() :
			expression->GetString() + " = " + std::to_string(expression->Evaluate());

		Utils::OutputToFile((prefix + info + "\n"));
	}
}

void WhyParser::Parse(std::vector<WhyToken>& tokens)
{
	//initializing static members
	Tokens = tokens; //TODO: refactor this
	currentTokenID = 0;
	currentToken = tokens[0];

	int expressionsNumber = 0;
	for(auto& t : tokens)
	{
		if(t.Is(WhyToken::Type::NewLine) || currentTokenID == 0)
		{
			if (currentTokenID != 0)
				TryAdvance();

			ParserNode* expression = GetExpression();
			std::string prefix = std::to_string(++expressionsNumber) + ") ";
			OutputExpression(expression, prefix);
			
			delete expression;
		}
	}	
}

int WhyParser::GetNumber()
{
	int result = 0;
	while (currentToken.Is(WhyToken::Type::Integer))
	{
		result = result * 10 + currentToken.GetValue();
		if (TryAdvance() == false)
			break;
	}
	return result;
}

ParserNode* WhyParser::GetExpression()
{
	ParserNode* term = GetTerm();

	while(true)
	{
		if (currentToken.Is(WhyToken::Type::OperPlus))
		{
			TryAdvance();
			ParserNode* nextTerm = GetTerm();
			term = new AddNode{ term, nextTerm };

		}
		else if (currentToken.Is(WhyToken::Type::OperMinus))
		{
			TryAdvance();
			ParserNode* nextTerm = GetTerm();
			term = new SubtractNode{ term, nextTerm };
		}
		else
			return term;
	}
}

ParserNode* WhyParser::GetTerm()
{
	ParserNode* factor = GetFactor();
	while(true)
	{
		if (currentToken.Is(WhyToken::Type::OperMultiply))
		{
			TryAdvance();
			ParserNode* nextFactor = GetFactor();
			factor = new MultiplicationNode{ factor,  nextFactor };
		}
		else if (currentToken.Is(WhyToken::Type::OperDivide))
		{
			TryAdvance();
			ParserNode* nextFactor = GetFactor();
			factor = new DivisionNode{ factor,  nextFactor };
		}
		else
			return factor;
	}
}

ParserNode* WhyParser::GetFactor()
{
	if (currentToken.Is(WhyToken::Type::Integer))
		return new IntegerNode{ GetNumber() };
	if (currentToken.Is(WhyToken::Type::String))
		return new StringNode{ GetString() };

	ParserNode* expression;
	if(currentToken.Is(WhyToken::Type::LBracket))
	{
		TryAdvance();
		expression = GetExpression();
		if (currentToken.Is(WhyToken::Type::RBracket))
		{
			TryAdvance();
			return expression;
		}
		else
			return nullptr;
	}
	if(currentToken.Is(WhyToken::Type::OperMinus))
	{
		TryAdvance();
		return new NegateNode{ GetFactor() };
	}
	return nullptr;
}

std::string WhyParser::GetString()
{
	std::string result;
	while (currentToken.Is(WhyToken::Type::String))
	{
		result = result + currentToken.GetString();
		if (TryAdvance() == false)
			break;
	}
	return result;
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

#include "WhyParser.h"

std::vector<WhyToken> WhyParser::Tokens;
unsigned int WhyParser::currentTokenID;
WhyToken WhyParser::currentToken = {WhyToken::Type::Undefined};

//DEBUG ONLY
static void OutputExpression(SharedNodePtr& expression, std::string prefix = 0)
{
	if (expression != nullptr)
	{
		std::string info =
			typeid(*expression).name() == typeid(StringNode).name() ?
			expression.get()->GetString() :
			expression.get()->GetString() + " = " + std::to_string(expression.get()->Evaluate());

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
	for(auto& token : tokens)
	{
		if(token.Is(WhyToken::Type::NewLine) || currentTokenID == 0)
		{
			if (currentTokenID != 0)
				TryAdvance();

			SharedNodePtr expression = GetExpression();

			std::string prefix = std::to_string(++expressionsNumber) + ") ";
			OutputExpression(expression, prefix);
		}
	}	
}

SharedNodePtr WhyParser::GetExpression()
{
	SharedNodePtr term = GetTerm();

	while(true)
	{
		if (currentToken.Is(WhyToken::Type::OperPlus))
		{
			TryAdvance();
			auto nextTerm = GetTerm();
			term = std::make_shared<AddNode>(term, nextTerm);

		}
		else if (currentToken.Is(WhyToken::Type::OperMinus))
		{
			TryAdvance();
			auto nextTerm = GetTerm();
			term = std::make_shared<SubtractNode>(term, nextTerm);
		}
		else return term;
	}
}

SharedNodePtr WhyParser::GetTerm()
{
	SharedNodePtr factor = GetFactor();

	while(true)
	{
		if (currentToken.Is(WhyToken::Type::OperMultiply))
		{
			TryAdvance();
			auto nextFactor = GetFactor();
			factor = std::make_shared<MultiplicationNode>(factor,  nextFactor);
		}
		else if (currentToken.Is(WhyToken::Type::OperDivide))
		{
			TryAdvance();
			auto nextFactor = GetFactor();
			factor = std::make_shared<DivisionNode>(factor, nextFactor);
		}
		else return factor;
	}
}

SharedNodePtr WhyParser::GetFactor()
{
	//if factor is just value
	if (currentToken.Is(WhyToken::Type::Integer))
		return std::make_shared<IntegerNode>(GetNumber());
	if (currentToken.Is(WhyToken::Type::String))
		return std::make_shared<StringNode>(GetString());

	//otherwise proceeds receiving 
	SharedNodePtr expression;

	if(currentToken.Is(WhyToken::Type::LBracket))
	{
		TryAdvance();
		expression = GetExpression();
		if (currentToken.Is(WhyToken::Type::RBracket))
		{
			TryAdvance();
			return expression;
		}
		else return nullptr;
	}
	if(currentToken.Is(WhyToken::Type::OperMinus))
	{
		TryAdvance();
		return GetFactor();
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

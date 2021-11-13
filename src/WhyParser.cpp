#include "WhyParser.h"

std::vector<SharedNodePtr> WhyParser::parserNodeTree;
std::map<std::string, SharedNodePtr> WhyParser::variables;

std::vector<WhyToken> WhyParser::Tokens;
unsigned int WhyParser::currentTokenID;
WhyToken WhyParser::currentToken = {WhyToken::Type::Undefined};

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

			if (currentToken.Is(WhyToken::Type::Variable))
			{
				std::string currentVarName = currentToken.GetString();
				//get what's being assigned
				TryAdvance();
				if (currentToken.Is(WhyToken::Type::Assign))
				{
					TryAdvance();
					//if this is the first encounter the variable should be stored
					auto varIterator = variables.find(currentVarName);
					if (varIterator == variables.end())
					{
						SharedNodePtr newNode = std::make_shared<VariableNode>(GetExpression(), currentVarName);
						auto&& newVariable = std::make_pair(currentVarName, newNode);
						variables.emplace(newVariable);
						parserNodeTree.push_back(newNode);
					}
					else
					{
						VariableNode* var = ((VariableNode*)varIterator->second.get());
						var->SetAssignedNode(GetExpression());
						parserNodeTree.push_back(varIterator->second);
					}
				}
				else
				{
					//todo: error
					continue;
				}
			}
			else if(currentToken.Is(WhyToken::Type::Print))
			{
				SharedNodePtr printNode = std::make_shared<PrintNode>(nullptr);
				PrintNode* printNodePtr = ((PrintNode*)printNode.get());
				TryAdvance();
				if(currentToken.Is(WhyToken::Type::File))
				{
					TryAdvance();
					printNodePtr->SetAssignedNode(std::make_shared<FileNode>(GetExpression()));
				}
				else 
				{
					printNodePtr->SetAssignedNode(GetExpression());
				}
				parserNodeTree.push_back(printNode);
			}
			else
			{
				//todo: throw an error
			}
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
	//if a variable exists then it's value has to be used
	//otherwise there is an error (uninitialized variable)
	if(currentToken.Is(WhyToken::Type::Variable))
	{
		auto varName = currentToken.GetString();
		auto varIterator = variables.find(varName);
		if(varIterator != variables.end())
		{
			VariableNode* var = ((VariableNode*)varIterator->second.get());
			TryAdvance();
			return var->GetValueNode();
		}
		else
		{
			//todo:throw an error
		}
	}

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

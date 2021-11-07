#include "ParserNode.h"

NumberNode::NumberNode(int& numberValue)
	: ParserNode{ token = { WhyToken::Type::Integer, numberValue } }
{
}

OperationNode::OperationNode(NumberNode left, WhyToken& token, NumberNode right)
	: ParserNode{ token }
{

}


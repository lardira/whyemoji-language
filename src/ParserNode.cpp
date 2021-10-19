#include "ParserNode.h"

NumberNode::NumberNode(WhyToken& token)
	: ParserNode { token }
{

}

OperationNode::OperationNode(NumberNode left, WhyToken& token, NumberNode right)
	: ParserNode{ token }
{

}


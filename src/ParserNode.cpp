#include "ParserNode.h"

MultiplicationNode::MultiplicationNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int MultiplicationNode::Evaluate()
{
	return left->Evaluate() * right->Evaluate();
}

DivisionNode::DivisionNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int DivisionNode::Evaluate()
{
	return left->Evaluate() / right->Evaluate();
}

AddNode::AddNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int AddNode::Evaluate()
{
	return left->Evaluate() + right->Evaluate();
}

SubtractNode::SubtractNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int SubtractNode::Evaluate()
{
	return left->Evaluate() - right->Evaluate();
}

NegateNode::NegateNode(ParserNode* node)
	: node(node) {}

int NegateNode::Evaluate()
{
	return -(node->Evaluate());
}

int IntegerNode::Evaluate()
{
	return IntegerNode::value;
}

IntegerNode::IntegerNode(int value)
	: value(value) {}

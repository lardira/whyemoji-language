#include "ParserNode.h"

MultiplicationNode::MultiplicationNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int MultiplicationNode::Evaluate()
{
	return left->Evaluate() * right->Evaluate();
}

std::string MultiplicationNode::GetString()
{
	return '(' + left->GetString() + " * " + right->GetString() + ')';
}

DivisionNode::DivisionNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int DivisionNode::Evaluate()
{
	return left->Evaluate() / right->Evaluate();
}

std::string DivisionNode::GetString()
{
	return '(' + left->GetString() + " / " + right->GetString() + ')';
}

AddNode::AddNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int AddNode::Evaluate()
{
	return left->Evaluate() + right->Evaluate();
}

std::string AddNode::GetString()
{
	return '(' + left->GetString() + " + " + right->GetString() + ')';
}

SubtractNode::SubtractNode(ParserNode* left, ParserNode* right)
	: left(left), right(right) {}

int SubtractNode::Evaluate()
{
	return left->Evaluate() - right->Evaluate();
}

std::string SubtractNode::GetString()
{
	return '(' + left->GetString() + " - " + right->GetString() + ')';
}

NegateNode::NegateNode(ParserNode* node)
	: node(node) {}

int NegateNode::Evaluate()
{
	return -(node->Evaluate());
}

std::string NegateNode::GetString()
{
	return '-' + node->GetString();
}

int IntegerNode::Evaluate()
{
	return IntegerNode::value;
}

IntegerNode::IntegerNode(int value)
	: value(value) {}

std::string IntegerNode::GetString()
{
	return std::to_string(value);
}

StringNode::StringNode(std::string text)
	: text(text) {}

int StringNode::Evaluate()
{
	return text.length();
}

std::string StringNode::GetString()
{
	return text;
}

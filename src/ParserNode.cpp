#include "ParserNode.h"

MultiplicationNode::MultiplicationNode(SharedNodePtr left, SharedNodePtr right)
	: left(left), right(right) {}

int MultiplicationNode::Evaluate()
{
	return left.get()->Evaluate() * right.get()->Evaluate();
}

std::string MultiplicationNode::GetString()
{
	return '(' + left.get()->GetString() + " * " + right.get()->GetString() + ')';
}

DivisionNode::DivisionNode(SharedNodePtr left, SharedNodePtr right)
	: left(left), right(right) {}

int DivisionNode::Evaluate()
{
	return left.get()->Evaluate() / right.get()->Evaluate();
}

std::string DivisionNode::GetString()
{
	return '(' + left.get()->GetString() + " / " + right.get()->GetString() + ')';
}

AddNode::AddNode(SharedNodePtr left, SharedNodePtr right)
	: left(left), right(right) {}

int AddNode::Evaluate()
{
	return left.get()->Evaluate() + right.get()->Evaluate();
}

std::string AddNode::GetString()
{
	return '(' + left.get()->GetString() + " + " + right.get()->GetString() + ')';
}

SubtractNode::SubtractNode(SharedNodePtr left, SharedNodePtr right)
	: left(left), right(right) {}

int SubtractNode::Evaluate()
{
	return left.get()->Evaluate() - right.get()->Evaluate();
}

std::string SubtractNode::GetString()
{
	return '(' + left.get()->GetString() + " - " + right.get()->GetString() + ')';
}

NegateNode::NegateNode(SharedNodePtr node)
	: node(node) {}

int NegateNode::Evaluate()
{
	return -(node.get()->Evaluate());
}

std::string NegateNode::GetString()
{
	return '-' + node.get()->GetString();
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

int ParserNode::Evaluate()
{
	return 0;
}

std::string ParserNode::GetString()
{
	return std::string();
}

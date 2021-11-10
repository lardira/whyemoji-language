#pragma once

#include "WhyToken.h"

class ParserNode
{
public:
	//not pure virtuals cuz of the shared ptrs
	virtual int Evaluate();
	virtual std::string GetString();
};

template<typename NodeType>
using SharedPtr = std::shared_ptr<NodeType>;
using SharedNodePtr = SharedPtr<ParserNode>;

class IntegerNode : public ParserNode
{
public:
	virtual int Evaluate() override;

	IntegerNode() = default;
	~IntegerNode() = default;
	IntegerNode(int value);
	virtual std::string GetString() override;
public:
	int value;
};

class MultiplicationNode : public ParserNode
{
public:
	MultiplicationNode() = default;
	~MultiplicationNode() = default;
	MultiplicationNode(SharedNodePtr left, SharedNodePtr right);

	virtual int Evaluate() override;
	virtual std::string GetString() override;
private:
	SharedNodePtr left;
	SharedNodePtr right;
};

class DivisionNode : public ParserNode
{
public:
	DivisionNode() = default;
	~DivisionNode() = default;
	DivisionNode(SharedNodePtr left, SharedNodePtr right);

	virtual int Evaluate() override;
	virtual std::string GetString() override;
private:
	SharedNodePtr left;
	SharedNodePtr right;
};

class AddNode : public ParserNode
{
public:
	AddNode() = default;
	~AddNode() = default;
	AddNode(SharedNodePtr left, SharedNodePtr right);

	virtual int Evaluate() override;
	virtual std::string GetString() override;
private:
	SharedNodePtr left;
	SharedNodePtr right;
};

class SubtractNode : public ParserNode
{
public:
	SubtractNode() = default;
	~SubtractNode() = default;
	SubtractNode(SharedNodePtr left, SharedNodePtr right);

	virtual int Evaluate() override;
	virtual std::string GetString() override;
private:
	SharedNodePtr left;
	SharedNodePtr right;
};

class NegateNode : public ParserNode
{
public:
	NegateNode() = default;
	~NegateNode() = default;
	NegateNode(SharedNodePtr node);

	virtual int Evaluate() override;
	virtual std::string GetString() override;
private:
	SharedNodePtr node;
};

class StringNode : public ParserNode
{
public:
	StringNode() = default;
	~StringNode() = default;
	StringNode(std::string text);

	//returns the length of the text value stored
	virtual int Evaluate() override;
	//returns the text
	virtual std::string GetString() override;
private:
	std::string text;
};

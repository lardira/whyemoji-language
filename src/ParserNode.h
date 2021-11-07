#pragma once

#include "WhyToken.h"

//TODO::make it unique ptrs
class ParserNode
{
public:
	virtual int Evaluate() = 0;
};

class IntegerNode : public ParserNode
{
public:
	virtual int Evaluate() override;

	IntegerNode() = default;
	~IntegerNode() = default;
	IntegerNode(int value);
public:
	int value;
};

class MultiplicationNode : public ParserNode
{
public:
	MultiplicationNode() = default;
	~MultiplicationNode() = default;
	MultiplicationNode(ParserNode * left, ParserNode * right);

	virtual int Evaluate() override;
private:
	ParserNode* left;
	ParserNode* right;
};

class DivisionNode : public ParserNode
{
public:
	DivisionNode() = default;
	~DivisionNode() = default;
	DivisionNode(ParserNode * left, ParserNode * right);

	virtual int Evaluate() override;
private:
	ParserNode* left;
	ParserNode* right;
};

class AddNode : public ParserNode
{
public:
	AddNode() = default;
	~AddNode() = default;
	AddNode(ParserNode* left, ParserNode* right);

	virtual int Evaluate() override;
private:
	ParserNode* left;
	ParserNode* right;
};

class SubtractNode : public ParserNode
{
public:
	SubtractNode() = default;
	~SubtractNode() = default;
	SubtractNode(ParserNode * left, ParserNode * right);

	virtual int Evaluate() override;
private:
	ParserNode* left;
	ParserNode* right;
};

class NegateNode : public ParserNode
{
public:
	NegateNode() = default;
	~NegateNode() = default;
	NegateNode(ParserNode* node);

	virtual int Evaluate() override;
private:
	ParserNode* node;
};


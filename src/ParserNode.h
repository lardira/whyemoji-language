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

	IntegerNode() = delete;
	~IntegerNode() = default;
	IntegerNode(int value);
	virtual std::string GetString() override;
public:
	int value;
};

class MultiplicationNode : public ParserNode
{
public:
	MultiplicationNode() = delete;
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
	DivisionNode() = delete;
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
	AddNode() = delete;
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
	SubtractNode() = delete;
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
	NegateNode() = delete;
	~NegateNode() = default;
	NegateNode(SharedNodePtr node);

	virtual int Evaluate() override;
	virtual std::string GetString() override;
private:
	SharedNodePtr node;
};

class VariableNode : public ParserNode
{
public:
	VariableNode() = delete;
	~VariableNode() = default;
	VariableNode(SharedNodePtr assignedNode, std::string name);

	virtual int Evaluate() override;
	virtual std::string GetString() override;
	SharedNodePtr GetValueNode() const;
	void SetAssignedNode(SharedNodePtr newValue);
private:
	SharedNodePtr assignedNode;
	std::string name;
};

class StringNode : public ParserNode
{
public:
	StringNode() = delete;
	~StringNode() = default;
	StringNode(std::string text);

	//returns the length of the text value stored
	virtual int Evaluate() override;
	//returns the text
	virtual std::string GetString() override;
private:
	std::string text;
};

class PrintNode : public ParserNode
{
public:
	PrintNode() = delete;
	~PrintNode() = default;
	PrintNode(SharedNodePtr whatToPrint);

	//returns the length of the text value stored
	virtual int Evaluate();
	//returns the text
	virtual std::string GetString() override;
	void SetAssignedNode(SharedNodePtr node);
	SharedNodePtr GetValueNode() const;
private:
	SharedNodePtr whatToPrint;
};

class FileNode : public ParserNode
{
public:
	FileNode() = delete;
	~FileNode() = default;
	FileNode(SharedNodePtr node);
	FileNode(SharedNodePtr node, std::string filePath);

	//returns the length of the text value stored
	virtual int Evaluate();
	//returns the text
	virtual std::string GetString() override;
	SharedNodePtr GetValueNode() const;
private:
	std::string filePath = "output.txt";
	SharedNodePtr node;
};

#pragma once

#include <iostream>
#include <string>

class WhyToken
{
public:
	enum class Type
	{
		Undefined,
		OperPlus,
		OperMinus,
		OperMultiply,
		OperDivide,
		Integer,
		String,
		NewLine,
		LBracket,
		RBracket,
	};
public:
	WhyToken() = delete;
	~WhyToken() = default;
	
	WhyToken(Type type, char value)
		: type(type), value(value) {}

	WhyToken(Type type)
		: type(type) {}

	int GetValue() const;
	WhyToken::Type GetType() const;
	std::string GetTypeToString() const;
private:
	Type type = Type::Undefined;
	int value = -1;

	std::string TypeToString() const;
};


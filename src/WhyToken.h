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
	};
public:
	WhyToken() = delete;
	~WhyToken() = default;
	
	WhyToken(Type type, char value)
		: type(type), value(value) {}

	WhyToken(Type type)
		: type(type) {}

	char GetValue() const;
	WhyToken::Type GetType() const;
	std::string GetTypeToString() const;
private:
	Type type = Type::Undefined;
	char value = -1;

	std::string TypeToString() const;
};


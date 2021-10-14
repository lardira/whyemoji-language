#pragma once
#include <iostream>
#include <string>

class Token
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

	Token() = delete;
	~Token() = default;
	
	Token(Type type, wchar_t value)
		: type(type), value(value) {}

	Token(Type type)
		: type(type) {}

	wchar_t GetValue() const;
	Token::Type GetType() const;
	std::string GetTypeToString() const;

private:
	Type type = Type::Undefined;
	wchar_t value = 0;

	std::string TypeToString() const;
};


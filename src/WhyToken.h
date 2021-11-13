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
		Variable,
		Print,
		Assign,
		File,
	};
public:
	WhyToken() = delete;
	~WhyToken() = default;
	WhyToken(Type type, int value);
	WhyToken(Type type, std::string value);
	WhyToken(Type type);

	int GetValue() const;
	WhyToken::Type GetType() const;
	bool Is(WhyToken::Type type) const;
	std::string GetTypeToString() const;
	std::string GetString() const;
private:
	Type type = Type::Undefined;
	int value = -1;
	std::string stringValue = std::string();

	std::string TypeToString() const;
};


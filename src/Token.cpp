#include "Token.h"

wchar_t Token::GetValue() const
{
	return value;
}

Token::Type Token::GetType() const
{
	return type;
}

std::string Token::GetTypeToString() const
{
	return Token::TypeToString();

}

std::string Token::TypeToString() const
{
	switch(type)
	{
	case Token::Type::OperPlus:
		return "OperPlus";
		break;

	case Token::Type::OperMinus:
		return "OperMinus";
		break;

	case Token::Type::OperMultiply:
		return "OperMultiply";
		break;

	case Token::Type::OperDivide:
		return "OperDivide";
		break;

	case Token::Type::Integer:
		return "Integer";
		break;

	case Token::Type::String:
		return "String";
		break;

	case Token::Type::Undefined: default:
		return "Undefined";
		break;
	}
}

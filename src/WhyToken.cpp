#include "WhyToken.h"

char WhyToken::GetValue() const
{
	return value;
}

WhyToken::Type WhyToken::GetType() const
{
	return type;
}

std::string WhyToken::GetTypeToString() const
{
	return WhyToken::TypeToString();
}

std::string WhyToken::TypeToString() const
{
	switch(type)
	{
	case WhyToken::Type::OperPlus:
		return "OperPlus";
		break;

	case WhyToken::Type::OperMinus:
		return "OperMinus";
		break;

	case WhyToken::Type::OperMultiply:
		return "OperMultiply";
		break;

	case WhyToken::Type::OperDivide:
		return "OperDivide";
		break;

	case WhyToken::Type::Integer:
		return "Integer";
		break;

	case WhyToken::Type::String:
		return "String";
		break;

	case WhyToken::Type::Undefined: default:
		return "Undefined";
		break;
	}
}

#include "WhyToken.h"

WhyToken::WhyToken(WhyToken::Type type, int value)
	: type(type), value(value) {}

WhyToken::WhyToken(WhyToken::Type type, std::string value)
	: type(type), stringValue(value) {}

WhyToken::WhyToken(WhyToken::Type type)
	: type(type) {}

int WhyToken::GetValue() const
{
	return value;
}

WhyToken::Type WhyToken::GetType() const
{
	return type;
}

bool WhyToken::Is(WhyToken::Type type) const
{
	return (GetType() == type);
}

std::string WhyToken::GetString() const
{
	return stringValue;
}

//for debug purposes
std::string WhyToken::GetTypeToString() const
{
	return WhyToken::TypeToString();
}

std::string WhyToken::TypeToString() const
{
	using TType = WhyToken::Type;

	switch(this->type)
	{
	case TType::OperPlus:
		return "OperPlus";
		break;

	case TType::OperMinus:
		return "OperMinus";
		break;

	case TType::OperMultiply:
		return "OperMultiply";
		break;

	case TType::OperDivide:
		return "OperDivide";
		break;

	case TType::Integer:
		return "Integer";
		break;

	case TType::String:
		return "String";
		break;
	
	case TType::NewLine:
		return "NewLine";
		break;

	case TType::LBracket:
		return "LBracket";
		break;

	case TType::RBracket:
		return "RBracket";
		break;

	case WhyToken::Type::Undefined: default:
		return "Undefined";
		break;
	}
}

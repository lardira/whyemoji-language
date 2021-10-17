#include "WhyLexer.h"

std::vector<WhyToken> WhyLexer::Tokens;

void WhyLexer::Tokenize(std::string& inputText)
{
	std::vector<std::string> stringTokens = Utils::GetUTF8Strings(inputText);

	for(auto& stringToken : stringTokens)
	{
		if (stringToken == u8"➕")
			Tokens.push_back({ WhyToken::Type::OperPlus });
		if (stringToken == u8"➖")
			Tokens.push_back({ WhyToken::Type::OperMinus });
		if (stringToken == u8"➗")
			Tokens.push_back({ WhyToken::Type::OperDivide });
		if (stringToken == u8"✖")
			Tokens.push_back({ WhyToken::Type::OperMultiply });
	}
}

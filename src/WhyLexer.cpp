#include "WhyLexer.h"

std::vector<WhyToken> WhyLexer::Tokens;

void WhyLexer::Tokenize(std::string& inputText)
{
	std::vector<std::string> stringTokens = Utils::GetUTF8Strings(inputText);

	for(unsigned int charID = 0; charID < stringTokens.size(); charID++)
	{
		//Operators
		if (stringTokens[charID] == u8"➕")
			Tokens.push_back({ WhyToken::Type::OperPlus });
		if (stringTokens[charID] == u8"➖")
			Tokens.push_back({ WhyToken::Type::OperMinus });
		if (stringTokens[charID] == u8"➗")
			Tokens.push_back({ WhyToken::Type::OperDivide });
		if (stringTokens[charID] == u8"✖")
			Tokens.push_back({ WhyToken::Type::OperMultiply });
		if (stringTokens[charID] == u8"〖")
			Tokens.push_back({ WhyToken::Type::LBracket });
		if (stringTokens[charID] == u8"〗")
			Tokens.push_back({ WhyToken::Type::RBracket });
		//Types
		if (stringTokens[charID] == u8"0")
			Tokens.push_back({WhyToken::Type::Integer, 0 });
		if (stringTokens[charID] == u8"1")
			Tokens.push_back({ WhyToken::Type::Integer, 1 });
		if (stringTokens[charID] == u8"2")
			Tokens.push_back({ WhyToken::Type::Integer, 2 });
		if (stringTokens[charID] == u8"3")
			Tokens.push_back({ WhyToken::Type::Integer, 3 });
		if (stringTokens[charID] == u8"4")
			Tokens.push_back({ WhyToken::Type::Integer, 4 });
		if (stringTokens[charID] == u8"5")
			Tokens.push_back({ WhyToken::Type::Integer, 5 });
		if (stringTokens[charID] == u8"6")
			Tokens.push_back({ WhyToken::Type::Integer, 6 });
		if (stringTokens[charID] == u8"7")
			Tokens.push_back({ WhyToken::Type::Integer, 7 });
		if (stringTokens[charID] == u8"8")
			Tokens.push_back({ WhyToken::Type::Integer, 8 });
		if (stringTokens[charID] == u8"9")
			Tokens.push_back({ WhyToken::Type::Integer, 9 });
		//Misc
		if (stringTokens[charID] == u8"\n")
			Tokens.push_back({ WhyToken::Type::NewLine });
		else if (stringTokens[charID] != u8" ")
			//TODO: Throw error message
			continue;
	}
}

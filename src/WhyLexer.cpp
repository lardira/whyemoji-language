#include "WhyLexer.h"

std::vector<WhyToken> WhyLexer::Tokens;

void WhyLexer::Tokenize(std::string& inputText)
{
	ClearTokens();

	std::vector<std::string> stringTokens = Utils::GetUTF8Strings(inputText);

	for (const auto& token : stringTokens)
	{
		TryGetOperator(token);
		TryGetObject(token);
		TryGetOtherTokens(token);
		
		//unless a token after all checks above is but an empty space 
		//it should be considered an error
		if (token == " ")
			continue; 
		else
		{
			//TODO::throw an error
		}
	}
}

void WhyLexer::TryGetOperator(const std::string& stringToken)
{
	if (stringToken == u8"➕")
		Tokens.push_back({ WhyToken::Type::OperPlus });
	else if (stringToken == u8"➖")
		Tokens.push_back({ WhyToken::Type::OperMinus });
	else if (stringToken == u8"➗")
		Tokens.push_back({ WhyToken::Type::OperDivide });
	else if (stringToken == u8"✖")
		Tokens.push_back({ WhyToken::Type::OperMultiply });
	else if (stringToken == u8"👉")
		Tokens.push_back({ WhyToken::Type::Assign });
	else if (stringToken == u8"〖")
		Tokens.push_back({ WhyToken::Type::LBracket });
	else if (stringToken == u8"〗")
		Tokens.push_back({ WhyToken::Type::RBracket });
}

void WhyLexer::TryGetObject(const std::string& stringToken)
{
	/*if (stringToken == u8"0")
		Tokens.push_back({ WhyToken::Type::Integer, 0 });
	if (stringToken == u8"1")
		Tokens.push_back({ WhyToken::Type::Integer, 1 });
	if (stringToken == u8"2")
		Tokens.push_back({ WhyToken::Type::Integer, 2 });
	if (stringToken == u8"3")
		Tokens.push_back({ WhyToken::Type::Integer, 3 });
	if (stringToken == u8"4")
		Tokens.push_back({ WhyToken::Type::Integer, 4 });
	if (stringToken == u8"5")
		Tokens.push_back({ WhyToken::Type::Integer, 5 });
	if (stringToken == u8"6")
		Tokens.push_back({ WhyToken::Type::Integer, 6 });
	if (stringToken == u8"7")
		Tokens.push_back({ WhyToken::Type::Integer, 7 });
	if (stringToken == u8"8")
		Tokens.push_back({ WhyToken::Type::Integer, 8 });
	if (stringToken == u8"9")
		Tokens.push_back({ WhyToken::Type::Integer, 9 });*/
	int tempTryInt;
	try 
	{
		tempTryInt = std::stoi(stringToken);
		if (tempTryInt >= 0 && tempTryInt <= 9)
			Tokens.push_back({ WhyToken::Type::Integer, tempTryInt });
	}
	catch(...)
	{
		if (stringToken >= u8"a" && stringToken <= u8"z")
			Tokens.push_back({ WhyToken::Type::String, stringToken });
		else if (stringToken >= u8"A" && stringToken <= u8"Z")
			Tokens.push_back({ WhyToken::Type::String, stringToken });
		else if (stringToken == u8"🤔")
			Tokens.push_back({ WhyToken::Type::Variable, stringToken});
		else if (stringToken == u8"🙂")
			Tokens.push_back({ WhyToken::Type::Variable, stringToken});
	}
}

void WhyLexer::TryGetOtherTokens(const std::string& stringToken)
{
	//Misc
	if (stringToken == u8"\n")
		Tokens.push_back({ WhyToken::Type::NewLine });
	else if(stringToken == u8"🖨")
		Tokens.push_back({ WhyToken::Type::Print });
	else if (stringToken == u8"💾")
		Tokens.push_back({ WhyToken::Type::File });
}

void WhyLexer::ClearTokens()
{
	Tokens.clear();
}

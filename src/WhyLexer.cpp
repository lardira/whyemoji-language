#include "WhyLexer.h"

std::vector<WhyToken> WhyLexer::Tokens;
std::vector<std::string> WhyLexer::possibleVariables = {
u8"😀", u8"😉", u8"😁", u8"😆", u8"😅", u8"😃", u8"😇", u8"🙃", u8"😄", u8"🙂", u8"😊", u8"🤣", u8"😂",
u8"🤩", u8"😘", u8"😗", u8"😍", u8"☺", u8"😙", u8"🥰", u8"😚", u8"🧐" ,u8"😎", u8"🤓" ,u8"🥳", u8"🤔",
u8"🤑", u8"🤪", u8"😜", u8"😛", u8"😋", u8"🤠",u8"🤢",u8"🤮",u8"🤕",u8"🥵",u8"🤒",u8"😵",u8"🥴",
u8"🤯", u8"😷", u8"🤧", u8"🥶", u8"🤤", u8"😴", u8"😪", u8"😔", u8"😌", u8"🤥", u8"🤐", u8"🙄", u8"😒",
u8"😑", u8"😏", u8"😬", u8"🤨", u8"😶", u8"😐", u8"🤫", u8"🤗", u8"🤭", u8"🤔", u8"🤑", u8"😝", u8"🤪",
u8"😜", u8"😛", u8"😋", u8"👽", u8"🤖", u8"🤡", u8"💩", u8"😠", u8"🤬", u8"👿", u8"💀", u8"😡", u8"😈",
u8"😤", u8"☠"
};


void WhyLexer::Tokenize(std::string& inputText)
{
	//should be cleared before reading a new file 
	ClearTokens();

	std::vector<std::string> stringTokens = Utils::GetUTF8Strings(inputText);

	for (const auto& token : stringTokens)
	{
		TryGetOperator(token);
		TryGetObject(token);
		TryGetOtherTokens(token);
		
		//unless a token after all checks above is but an empty space 
		//it should be considered an error
		if (token != " ")
			continue; //TODO::throw an error
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
	int tempTryInt;
	//if string to int throws an exception then it's not int
	//thus other token types should be considered
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
		else 
		{
			auto result = std::find(possibleVariables.begin(), possibleVariables.end(), stringToken);
			if (result != possibleVariables.end())
				Tokens.push_back({ WhyToken::Type::Variable, stringToken });
		}
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

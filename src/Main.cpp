#include <iostream>

#include "Utils.h"
#include "WhyLexer.h"
#include "WhyParser.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(""));

	std::string inputText = Utils::ReadInputFile(Utils::INPUT_PATH);
	
	WhyLexer::Tokenize(inputText);

	WhyParser::Parse(WhyLexer::Tokens);

	/*std::cout << "All Tokens in file: \n";
	Utils::PrintTokens(WhyLexer::Tokens);*/

	return 0;
}
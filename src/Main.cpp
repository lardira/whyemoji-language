#include <iostream>

#include "WhyLexer.h"
#include "WhyParser.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(""));

	const std::string inputFile = "test/test.why";
	const std::string outputFile = "test/output.why";

	std::string inputText = Utils::ReadInputFile(inputFile);
	WhyLexer::Tokenize(inputText);
	WhyParser::Parse(WhyLexer::Tokens);

	Utils::PrintTokens(WhyLexer::Tokens);

	return 0;
}
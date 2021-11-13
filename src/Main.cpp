#include <iostream>

#include "WhyLexer.h"
#include "WhyParser.h"
#include "WhyEvaluator.h"
#include "Utils.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(""));

	std::string inputText = Utils::ReadInputFile(Utils::INPUT_PATH);
	std::vector<SharedNodePtr> expressions;
	
	WhyLexer::Tokenize(inputText);
	WhyParser::Parse(WhyLexer::Tokens);
	WhyEvaluator::Evaluate(WhyParser::parserNodeTree);

	/*std::cout << "All Tokens in file: \n";
	Utils::PrintTokens(WhyLexer::Tokens);*/

	return 0;
}
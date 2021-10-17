#include <iostream>

#include "WhyLexer.h"


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(""));

	std::string inputFile = "test/test.why";
	std::string outputFile = "test/output.why";

	std::string inputText = Utils::ReadInputFile(inputFile);
	WhyLexer::Tokenize(inputText);
	return 0;
}
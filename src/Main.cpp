#include <iostream>

#include "WhyLexer.h"
#include "WhyParser.h"
#include "WhyEvaluator.h"
#include "Utils.h"
#include "FileManager.h"

int GetChoice()
{
	int a;
	std::cin >> a;
	std::cout << '\n' << std::endl;
	return a;
}

std::string GetInputFromMenu()
{
	std::cout << "1. assign filepath to code" << '\n';
	std::cout << "2. use default (test/test.why)" << '\n' << '>';
	int answer = GetChoice();

	switch (answer)
	{
	case 1:
	{
		std::string newFilePath;
		while (newFilePath.size() < 3 || newFilePath.substr(newFilePath.size() - 4, 4) != ".why")
		{
			std::cout << "type new file path:\n" << '>';
			std::cin >> newFilePath;
		}
		return FileManager::ReadInputFile(newFilePath);
		break;
	}
	case 2:
		return FileManager::ReadInputFile(FileManager::INPUT_PATH);
		break;
	default:
		std::cout << "there is no such option" << "\n";
		return std::string();
		break;
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(""));


	std::string inputFileText = GetInputFromMenu();
	
	if(inputFileText.size() > 0)
	{
		WhyLexer::Tokenize(inputFileText);
		WhyParser::Parse(WhyLexer::Tokens);
		WhyEvaluator::Evaluate(WhyParser::parserNodeTree);
	}
	else
	{
		std::cout << "the file was not found or empty";
		return 1;
	}

	return 0;
}
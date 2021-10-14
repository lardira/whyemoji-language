#include <iostream>
#include <fstream>
#include <sstream>

#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include "windows.h"

#include "Token.h"

std::wstring ReadInputFile(std::string inputFile)
{
	std::wifstream istream(inputFile, (std::ios::binary | std::ios::in));
	if (istream.is_open() == false)
		return L"";

	std::wstringstream input;
	input << istream.rdbuf();
	std::wstring inputString = input.str();
	istream.close();

	return input.str();
}

int OutputToFile(std::string outputFile, std::wstring output)
{
	bool isSuccess = false;

	std::wofstream ostream(outputFile, (std::ios::binary | std::ios::out));
	isSuccess = ostream.is_open();
	
	if(isSuccess)
		ostream << output;

	return isSuccess;
}

int main()
{
	_setmode(_fileno(stdout), _O_WTEXT);
	SetConsoleOutputCP(CP_UTF8);
	//Token token1{ Token::Type::Integer, L"\u1F600" };
	std::string inputFile = "test/test.why";
	std::string outputFile = "test/output.why";

	std::wstring input = ReadInputFile(inputFile);
	std::wcout << input << L'\n';
	std::wcout << "Successfully compiled: " << OutputToFile(outputFile, input);
	return 0;
}
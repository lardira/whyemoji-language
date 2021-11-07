#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <codecvt>
#include <vector>
#include "windows.h"

#include "WhyToken.h"

namespace Utils
{
#define UTF8_1B_MASK 0b10000000
#define UTF8_1B_COUNT 0

#define UTF8_2B_MASK 0b11100000
#define UTF8_2B_COUNT 0b11000000

#define UTF8_3B_MASK 0b11110000
#define UTF8_3B_COUNT 0b11100000

#define UTF8_4B_MASK 0b11111000 
#define UTF8_4B_COUNT 0b11110000

	const std::string INPUT_PATH = "test/test.why";
	const std::string OUTPUT_PATH = "test/output.why";

	static int GetUTF8CodePointSize(char c)
	{
		if ((c & UTF8_1B_MASK) == UTF8_1B_COUNT) 
			return 1;
		if ((c & UTF8_2B_MASK) == UTF8_2B_COUNT) 
			return 2;
		if ((c & UTF8_3B_MASK) == UTF8_3B_COUNT) 
			return 3;
		if((c & UTF8_4B_MASK) == UTF8_4B_COUNT)
			return 4;
		return 0;
		// TODO: what should happen if a byte with prefix 0b10xxxxxx is passed?
	}

	static void PrintTokens(std::vector<WhyToken>& tokens)
	{
		for(auto& token : tokens)
		{
			std::string tokenValue = 
				token.GetValue() == -1 ? std::string() : std::to_string(token.GetValue());
			std::cout << "{ " << token.GetTypeToString() << " val: " << tokenValue << " }\n";
		}
	}

	static std::vector<std::string> GetUTF8Strings(std::string string)
	{
		std::vector<std::string> utf8strings;
		const char* chars = string.c_str();
		int bytesNum = string.length();
		int i = 0;

		while (i != bytesNum)
		{
			int c = i;
			i += GetUTF8CodePointSize(chars[i]);

			std::string utf8string;
			for (; c < i; c++)
				utf8string = utf8string + chars[c];

			utf8strings.push_back(utf8string);
		}
		return utf8strings;
	}

	static std::string ReadInputFile(std::string inputFile)
	{

		std::ifstream istream(inputFile, (std::ios::binary | std::ios::in));

		if (istream.is_open() == false)
			return std::string();

		std::stringstream input;
		input << istream.rdbuf();

		istream.close();
		return input.str();
	}

	static int OutputToFile(std::string output, std::string outputFile = OUTPUT_PATH)
	{
		bool isSuccess = false;

		std::ofstream ostream(outputFile, (std::ios::binary | std::ios::out | std::ios_base::app));
		ostream.imbue(std::locale("en_US.UTF-8"));

		isSuccess = ostream.is_open();

		if (isSuccess)
			ostream << output;

		ostream.close();
		return isSuccess;
	}
}
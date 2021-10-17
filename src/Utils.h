#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include "windows.h"

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

#define UTF8_OTHER_MASK 0b00111111

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

	static int OutputToFile(std::string outputFile, std::string output)
	{
		bool isSuccess = false;

		std::ofstream ostream(outputFile, (std::ios::binary | std::ios::out));
		ostream.imbue(std::locale("en_US.UTF-8"));

		isSuccess = ostream.is_open();

		if (isSuccess)
			ostream << output;

		return isSuccess;
	}

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
}
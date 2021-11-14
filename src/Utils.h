#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <codecvt>
#include <vector>
#include "windows.h"

#include "WhyToken.h"
#include "ParserNode.h"

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

	static void PrintTokens(std::vector<WhyToken>& tokens)
	{
		for(auto& token : tokens)
		{
			//clearing value for output
			std::string tokenValue = token.GetValue() == -1 ? std::string() : std::to_string(token.GetValue());
			std::cout << "{ " << token.GetTypeToString() << " val: " << tokenValue << " }\n";
		}
	}

	template<typename T>
	static bool CompareNodeTypeTo(SharedNodePtr nodeTypeOfToCompare)
	{
		if (nodeTypeOfToCompare.get() == nullptr)
			return false;

		//using just right values cuz otherwise the strings are going to be allocated on the heap
		std::string&& a = typeid(T).name();
		std::string&& b = typeid(*nodeTypeOfToCompare).name();
		return (a == b);
	}

	static void Print(SharedNodePtr expression, std::string prefix = std::string())
	{
		if (expression != nullptr)
		{
			std::string info;
			if (CompareNodeTypeTo<StringNode>(expression))
			{
				info = expression.get()->GetString();
			}
			else if (CompareNodeTypeTo<VariableNode>(expression))
			{
				auto variablePtr = ((VariableNode*)expression.get());
				Print(variablePtr->GetValueNode(), prefix);
				return;
			}
			else
				info = std::to_string(expression.get()->Evaluate());

			std::cout << prefix << info << '\n';
		}
	}
}
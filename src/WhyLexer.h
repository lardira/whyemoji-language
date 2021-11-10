#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Utils.h"
#include "WhyToken.h"

class WhyLexer
{
public:
	WhyLexer() = default;
	~WhyLexer() = default;

	static std::vector<WhyToken> Tokens;
	static void Tokenize(std::string& inputText);
	static void ClearTokens();
};


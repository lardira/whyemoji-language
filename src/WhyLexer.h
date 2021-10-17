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

	static void Tokenize(std::string& inputText);
	static std::vector<WhyToken> Tokens;
};


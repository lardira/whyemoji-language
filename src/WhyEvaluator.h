#pragma once

#include "ParserNode.h"
#include "WhyParser.h"
#include "WhyVariable.h"
#include "Utils.h"

class WhyEvaluator
{
public:
	WhyEvaluator() = default;
	~WhyEvaluator() = default;

	static void Evaluate(std::vector<SharedNodePtr> parserNodeTree);
private:
	static std::vector<WhyVariable<int>> integers;
};


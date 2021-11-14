#pragma once

#include "ParserNode.h"
#include "WhyParser.h"
#include "Utils.h"
#include "FileManager.h"

class WhyEvaluator
{
public:
	WhyEvaluator() = default;
	~WhyEvaluator() = default;

	static void Evaluate(std::vector<SharedNodePtr> parserNodeTree);
	static void Print(SharedNodePtr& expression);
};


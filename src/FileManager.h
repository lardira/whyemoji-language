#pragma once
#include "Utils.h"
#include "ParserNode.h"

namespace FileManager{

const std::string INPUT_PATH = "test/test.why";
const std::string OUTPUT_PATH = "test/output.why";

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

static void PrintToFile(SharedNodePtr expression, std::string prefix = std::string())
{
	if (expression != nullptr)
	{
		std::string info;
		if (Utils::CompareNodeTypeTo<StringNode>(expression))
		{
			info = expression.get()->GetString();
		}
		else if (Utils::CompareNodeTypeTo<VariableNode>(expression))
		{
			auto variablePtr = ((VariableNode*)expression.get());
			PrintToFile(variablePtr->GetValueNode(), prefix);
			return;
		}
		else
			info = std::to_string(expression.get()->Evaluate());

		OutputToFile((prefix + info + "\n"));
	}
}

}
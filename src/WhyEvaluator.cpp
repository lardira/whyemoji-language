#include "WhyEvaluator.h"

std::vector<WhyVariable<int>> WhyEvaluator::integers;

void WhyEvaluator::Evaluate(std::vector<SharedNodePtr> parserNodeTree)
{
	for (auto& expression : parserNodeTree)
		if (Utils::CompareNodeTypeTo<PrintNode>(expression))
		{
			auto printNode = (PrintNode*)expression.get();
			auto whatToPrint = printNode->GetValueNode();
			if (Utils::CompareNodeTypeTo<FileNode>(whatToPrint))
			{
				auto fileNode = (FileNode*)whatToPrint.get();
				Utils::PrintToFile(fileNode->GetValueNode(), ">");
			}
			else
			{
				Utils::Print(whatToPrint, ">");
			}
		}
}

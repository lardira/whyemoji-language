#include "WhyEvaluator.h"

void WhyEvaluator::Evaluate(std::vector<SharedNodePtr> parserNodeTree)
{
	for (auto& expression : parserNodeTree)
		if (Utils::CompareNodeTypeTo<PrintNode>(expression))
		{
			Print(expression);
		}
}

void WhyEvaluator::Print(SharedNodePtr& expression)
{
	auto printNode = (PrintNode*)expression.get();
	auto whatToPrint = printNode->GetValueNode();
	//if filenode is found after print node then file manager must be called
	if (Utils::CompareNodeTypeTo<FileNode>(whatToPrint))
	{
		auto fileNode = (FileNode*)whatToPrint.get();

		FileManager::PrintToFile(fileNode->GetValueNode(), ">");
	}
	else
	{
		Utils::Print(whatToPrint, "Output:\n");
	}
}

#include "MdSectionRule.h"

const MdSectionType* MdSectionRule::GetTypeFromStartRules(std::string text)
{
	static MdSectionType titleType = MdSectionType::title;
	static MdSectionType textType = MdSectionType::text;

	if (!text.empty() && text[0] == '#')
	{
		return &titleType;
	}

	return &textType;
}

std::list<std::string> MdSectionRule::GetOXmlTypename(MdSectionType type)
{
	if (type == MdSectionType::title)
	{
		return { "Paragraph", "Run" };
	}

	return { "Paragraph" };
}

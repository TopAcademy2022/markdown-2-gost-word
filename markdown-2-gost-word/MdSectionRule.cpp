#include "MdSectionRule.h"

MdSectionType MdSectionRule::GetTypeFromStartRules(std::string text)
{
	return MdSectionType::text;
}

std::list<std::string> MdSectionRule::GetOXmlTypename(MdSectionType type)
{
	return std::list<std::string>();
}

#include "MdSectionParser.h"

std::list<MdSection*> MdSectionParser::ParseText(std::string text)
{
	std::list<MdSection*> result;
    MdSectionRule mdRules;

    if (!text.empty())
    {
        const MdSectionType* section = mdRules.GetTypeFromStartRules(text);
        if (section != nullptr)
        {
            result.push_back(new MdSection(text, *section));
        }
    }

    return result;
}

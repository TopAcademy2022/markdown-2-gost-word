#include "MdSectionParser.h"

std::list<MdSection*> MdSectionParser::ParseText(std::string text)
{
	std::list<MdSection*> result;
    MdSectionRule mdRules;

    const char* tmpText = text.c_str();

    do
    {
        // Find first
        MdSectionType section = mdRules.GetTypeFromStartRules(text);

        // Find next

        // Substring

        // If not sections => set empty
    } while (!text.empty());

    return result;
}

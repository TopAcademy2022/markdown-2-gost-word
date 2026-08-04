#include "MdSectionParser.h"
#include <sstream>
#include <string>
#include <list>

std::list<MdSection*> MdSectionParser::ParseText(std::string text)
{
    std::list<MdSection*> result;
    MdSectionRule mdRules;

    if (text.empty())
    {
        return result;
    }

    std::istringstream stream(text);
    std::string line;
    std::string segment;

    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            if (!segment.empty())
            {
                auto sectionType = mdRules.GetTypeFromStartRules(segment);
                if (sectionType)
                {
                    result.push_back(new MdSection(segment, *sectionType));
                }
                segment.clear();
            }
        }
        else
        {
            segment += line + "\n";
        }
    }

    if (!segment.empty())
    {
        auto sectionType = mdRules.GetTypeFromStartRules(segment);
        if (sectionType)
        {
            result.push_back(new MdSection(segment, *sectionType));
        }
    }

    return result;
}
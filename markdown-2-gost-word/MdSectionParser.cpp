#include "MdSectionParser.h"
#include <sstream>
#include <string>
#include <list>

namespace
{
	bool IsBlankLine(const std::string& line)
	{
		return line.find_first_not_of(" \t\r") == std::string::npos;
	}
}

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
		if (IsBlankLine(line))
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
			if (!line.empty() && line.back() == '\r')
			{
				line.pop_back();
			}

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

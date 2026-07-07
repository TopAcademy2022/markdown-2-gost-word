#include "MdSectionParser.h"
#include <sstream> 
#include <string>
#include <list>
std::list<MdSection*> MdSectionParser::ParseText(std::string text)
{
    std::list<MdSection*> result = std::list<MdSection*>();
    MdSectionRule mdRules;

   if (!text.empty())
    {
        const MdSectionType* section = mdRules.GetTypeFromStartRules(text);
        if (section != nullptr)
        {
            result.push_back(new MdSection(text, *section));
        }
    }
    //return result;//конец первоначаль шаблона, нужно ли???????? что делать потом с гитом 
        std::istringstream stream(text);
        std::string line;
        std::string segment;

        while (std::getline(stream, line))
        {
            if (line.empty())
            {
                if (!segment.empty())
                {
                    auto sectionType = mdRules.GetTypeFromStartRules(segment);// определяем тип блока и создаём секцию
                    if (sectionType)
                        result.push_back(new MdSection(segment, *sectionType));
                    segment.clear();
                }
            }
            else
            {
                segment += line + "\n";// не пустая сторока = сегмент 
            }
        }
        if (!segment.empty()) //последний блок без пустой строки в конце
        {
            auto sectionType = mdRules.GetTypeFromStartRules(segment);
            if (sectionType)
                result.push_back(new MdSection(segment, *sectionType));
        }

        return result;
    }
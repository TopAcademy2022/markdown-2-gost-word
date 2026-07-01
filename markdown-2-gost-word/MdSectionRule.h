#pragma once


#include <list>
#include <string>

#include "MdSectionType.h"


class MdSectionRule
{
private:
	// Where or with what a section begins (for example, with #). if.startWith(‘#’) - MdSectionType::title
	std::list<std::string> _startSectionRules;

	// How should section # be converted in GOST Word?  MdSectionType::title - Paragraph ParagraphProperties.Indentation {Left = "720"};
	std::list<std::string> _convertSectionRules;

public:
	MdSectionType GetTypeFromStartRules(std::string text);

	std::list<std::string> GetOXmlTypename(MdSectionType type);
};


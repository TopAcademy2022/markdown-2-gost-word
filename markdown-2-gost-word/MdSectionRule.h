#pragma once

#include <list>
#include <map>
#include <string>

#include "MdSectionType.h"


// Dictionary key is MdSectionType, value is a rule string.
class MdSectionRule
{
private:
	// Where or with what a section begins. Example: MdSectionType::title starts with "#".
	std::map<MdSectionType, std::string> _startSectionRules;

	// How a Markdown section type should be converted to GOST Word/OpenXML objects.
	std::map<MdSectionType, std::string> _convertSectionRules;

public:
	// Get the section type based on the text, or nullptr when no rule matches.
	const MdSectionType* GetTypeFromStartRules(std::string text);

	// Get OpenXML type names used by the target GOST Word representation.
	std::list<std::string> GetOXmlTypename(MdSectionType type);
};
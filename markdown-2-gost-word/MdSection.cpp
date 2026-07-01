#include "MdSection.h"

bool MdSection::CheckCorrectType(std::string text, MdSectionType sectionType)
{
	MdSectionRule mdRules;

	MdSectionType section = mdRules.GetTypeFromStartRules(text);

	if (section == sectionType)
	{
		return true;
	}

	return false;
}

MdSection::MdSection(std::string text, MdSectionType sectionType)
{
	if (CheckCorrectType(text, sectionType))
	{
		this->_text = text;
		this->_sectionType = sectionType;
	}
	else
	{
		// Throw new error
	}
}

MdSectionType MdSection::GetSectionType()
{
	return this->_sectionType;
}

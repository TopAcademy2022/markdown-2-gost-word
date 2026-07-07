#include "MdSection.h"

bool MdSection::CheckCorrectType(std::string text, MdSectionType sectionType)
{
	MdSectionRule mdRules;
	const MdSectionType* detectedType = mdRules.GetTypeFromStartRules(text);

	if (detectedType != nullptr && sectionType == *detectedType)
	{
		return true;
	}

	return false;
}

MdSection::MdSection(std::string text, MdSectionType sectionType)
	: _sectionType(MdSectionType::text)
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

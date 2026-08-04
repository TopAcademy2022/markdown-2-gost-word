#pragma once

#include <string>

#include "MdSectionType.h"
#include "MdSectionRule.h"


class MdSection
{
private:
	MdSectionType _sectionType;

	std::string _text;

	bool CheckCorrectType(std::string text, MdSectionType sectionType);

public:
	MdSection(std::string text, MdSectionType sectionType);

	MdSectionType GetSectionType();

	std::string GetText()
	{
		return this->_text;
	}
};

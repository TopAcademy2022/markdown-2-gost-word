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

	// Returns the value that must be written to the document, without
	// Markdown block markers and the trailing line break.
	std::string GetContent() const;
};

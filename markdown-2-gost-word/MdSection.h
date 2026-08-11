#pragma once

#include <string>

#include "MdSectionType.h"
#include "MdSectionRule.h"


class MdSection
{
private:
	MdSectionType _sectionType;
	
	std::string _text;

	int _headingLevel;

	bool CheckCorrectType(std::string text, MdSectionType sectionType);

public:
	MdSection(std::string text, MdSectionType sectionType);

	MdSectionType GetSectionType();

	int GetHeadingLevel() const {
		return this->_headingLevel;
	}
	std::string GetText()
	{
		return this->_text;
	}

	// Returns the value that must be written to the document, without
	// Markdown block markers and the trailing line break.
	std::string GetContent() const;
};

#include "MdSection.h"

#include <cctype>

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

std::string MdSection::GetContent() const
{
	std::string content = _text;

	while (!content.empty() && (content.back() == '\n' || content.back() == '\r'))
	{
		content.pop_back();
	}

	if (_sectionType == MdSectionType::title)
	{
		size_t markerEnd = 0;
		while (markerEnd < content.size() && content[markerEnd] == '#')
		{
			++markerEnd;
		}

		while (markerEnd < content.size()
			&& std::isspace(static_cast<unsigned char>(content[markerEnd])))
		{
			++markerEnd;
		}

		content.erase(0, markerEnd);
	}

	return content;
}

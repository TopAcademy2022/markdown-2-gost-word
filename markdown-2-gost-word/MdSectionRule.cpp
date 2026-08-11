#include "MdSectionRule.h"

#include <cctype>
	
namespace
{
	bool IsListItem(const std::string& text)
	{
		size_t position = 0;
		while (position < text.size() && (text[position] == ' ' || text[position] == '\t'))
		{
			++position;
		}

		if (position + 1 < text.size()
			&& (text[position] == '-' || text[position] == '*' || text[position] == '+')
			&& std::isspace(static_cast<unsigned char>(text[position + 1])))
		{
			return true;
		}

		size_t digitEnd = position;
		while (digitEnd < text.size()
			&& std::isdigit(static_cast<unsigned char>(text[digitEnd])))
		{
			++digitEnd;
		}

		return digitEnd > position
			&& digitEnd + 1 < text.size()
			&& (text[digitEnd] == '.' || text[digitEnd] == ')')
			&& std::isspace(static_cast<unsigned char>(text[digitEnd + 1]));
	}
}

const MdSectionType* MdSectionRule::GetTypeFromStartRules(std::string text)
{
	static MdSectionType titleType = MdSectionType::title;
	static MdSectionType textType = MdSectionType::text;

	if (!text.empty() && text[0] == '#')
	{
		size_t hashtagCount = 0;
		while (hashtagCount < text.size() && text[hashtagCount] == '#') {
			++hashtagCount;
		}
		if (hashtagCount >= 1 && hashtagCount <= 6) {
			if (hashtagCount == text.size() || std::isspace(static_cast<unsigned char>(text[hashtagCount]))) {
				return &titleType;
			}
		}
		
	}

	// Lists are deliberately unsupported until a corresponding section type
	// and conversion rule are introduced.
	if (IsListItem(text))
	{
		return nullptr;
	}

	return &textType;
}

std::list<std::string> MdSectionRule::GetOXmlTypename(MdSectionType type)
{
	if (type == MdSectionType::title)
	{
		return { "Paragraph", "Run", "Text {Value = %}" };
	}

	return { "Paragraph", "Run", "Text {Value = %}" };
}

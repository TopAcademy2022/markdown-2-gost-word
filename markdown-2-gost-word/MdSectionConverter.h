#pragma once

#include "FormattingProfile.h"


#include <functional>
#include <list>

#include "GostWordSection.h"
#include "MdSection.h"
#include "OpenXmlApi.h"
#include "ClrParser.h"
#include "OpenXmlService.h"


class MdSectionConverter
{
private:
	std::list<GostWordSection> _gostWordSection;

	void ConvertToGostSections(std::list<MdSection*> sections);

public:
	MdSectionConverter(std::list<MdSection*> sections);
	~MdSectionConverter();

	XmlServiceStatus SaveToGostWord(const std::wstring& outputPath);
	XmlServiceStatus SaveToGostWord(const std::wstring& outputPath, const FormattingProfile& profile);
};


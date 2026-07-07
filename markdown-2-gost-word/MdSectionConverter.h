#pragma once

#include <list>

#include "GostWordSection.h"
#include "MdSection.h"
#include "OpenXmlApi.h"


class MdSectionConverter
{
private:
	std::list<GostWordSection*> _gostWordSection;

	void ConvertToGostSections(std::list<MdSection*> sections);

public:
	MdSectionConverter(std::list<MdSection*> sections);
	~MdSectionConverter();

	XmlServiceStatus SaveToGostWord();
};


#pragma once

#include <list>

#include "MdSection.h"
#include "OpenXmlApi.h"


class MdSectionConverter
{
private:
	void ConvertToGostSections(std::list<MdSection*> sections);

public:
	MdSectionConverter(std::list<MdSection*> sections);

	XmlServiceStatus SaveToGostWord();
};


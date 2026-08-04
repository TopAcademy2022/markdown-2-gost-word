#pragma once

#include <list>
#include <vcclr.h>

using namespace DocumentFormat::OpenXml::Wordprocessing;
using namespace DocumentFormat::OpenXml;
using namespace System::Collections::Generic;

class GostWordSection
{
private:
	// Set of OpenXML objects for the first section of GOST Word
	gcroot<List<OpenXmlElement^>^> _sectionData;

public:
	GostWordSection();
	explicit GostWordSection(List<OpenXmlElement^>^ sectionData);

	List<OpenXmlElement^>^ GetSectionData();

	static Document^ CombineListSections(std::list<GostWordSection> sections);
};

#pragma once

#include <list>
#include <vcclr.h>

using namespace DocumentFormat::OpenXml::Wordprocessing;

class GostWordSection
{
private:
	// Set of OpenXML objects for the first section of GOST Word
	gcroot<array<System::Object^>^> _sectionData;

public:
	GostWordSection();
	explicit GostWordSection(array<System::Object^>^ sectionData);

	array<System::Object^>^ GetSectionData();

	static Document^ CombineListSections(std::list<GostWordSection*> sections);
};

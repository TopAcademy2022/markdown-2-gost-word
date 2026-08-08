#include "GostWordSection.h"

GostWordSection::GostWordSection()
	: _sectionData(nullptr)
{
}

GostWordSection::GostWordSection(OpenXmlElement^ sectionData)
	: _sectionData(sectionData)
{
}

OpenXmlElement^ GostWordSection::GetSectionData()
{
	return _sectionData;
}

Document^ GostWordSection::CombineListSections(std::list<GostWordSection> sections)
{
	Body^ body = gcnew Body();
	for (GostWordSection& section : sections)
	{
		OpenXmlElement^ root = section.GetSectionData();
		if (root != nullptr)
		{
			body->AppendChild<OpenXmlElement^>(root);
		}
	}

	Document^ document = gcnew Document();
	document->AppendChild<Body^>(body);
	return document;
}

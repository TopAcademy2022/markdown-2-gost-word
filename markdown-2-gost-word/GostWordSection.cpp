#include "GostWordSection.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace DocumentFormat::OpenXml;
using namespace DocumentFormat::OpenXml::Packaging;
using namespace DocumentFormat::OpenXml::Wordprocessing;

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
	Paragraph^ currentParagraph = nullptr;
	Run^ currentRun = nullptr;

	for (GostWordSection* section : sections)
	{
		for each(System::Object ^ obj in section->GetSectionData())
		{
			OpenXmlElement^ element = dynamic_cast<OpenXmlElement^>(obj);

			if (element != nullptr)
			{
				body->Append(element->CloneNode(true));
			}
		}
	}

	// TODO: how combine to 1 Document
	return gcnew Document();
}

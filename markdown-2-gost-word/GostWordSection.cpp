#include "GostWordSection.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace DocumentFormat::OpenXml;
using namespace DocumentFormat::OpenXml::Packaging;
using namespace DocumentFormat::OpenXml::Wordprocessing;

GostWordSection::GostWordSection()
	: _sectionData(gcnew array<System::Object^>(0))
{
}

GostWordSection::GostWordSection(array<System::Object^>^ sectionData)
	: _sectionData(sectionData == nullptr ? gcnew array<System::Object^>(0) : sectionData)
{
}

array<System::Object^>^ GostWordSection::GetSectionData()
{
	return _sectionData;
}

Document^ GostWordSection::CombineListSections(std::list<GostWordSection*> sections)
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

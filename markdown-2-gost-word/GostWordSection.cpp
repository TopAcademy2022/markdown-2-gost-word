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
	System::Collections::Generic::List<array<System::Object^>^> someSections;

	Body^ body = gcnew Body();
	Paragraph^ currentParagraph = nullptr;
	Run^ currentRun = nullptr;

	array<System::Object^>^ sectionData1 = gcnew array<System::Object^>
	{
		gcnew Paragraph(),
			gcnew Run(),
			gcnew Text("Hello")
	};
	GostWordSection* sec1 = new GostWordSection(sectionData1);
	someSections.Add(sec1->_sectionData);

	array<System::Object^>^ sectionData2 = gcnew array<System::Object^>
	{
		gcnew Run(),
		gcnew Text("Hello2")
	};
	GostWordSection* sec2 = new GostWordSection(sectionData2);
	someSections.Add(sec2->_sectionData);

	for each (array<System::Object^> ^ section in someSections)
	{
		System::Console::WriteLine(section + "\n\n");
		for each (System::Object ^ obj in section)
		{
			body->AppendChild(obj);
		}
	}

	// TODO: how combine to 1 Document
	return gcnew Document();
}

#include "GostWordSection.h"

GostWordSection::GostWordSection()
	: _sectionData(gcnew List<OpenXmlElement^>)
{
}

GostWordSection::GostWordSection(List<OpenXmlElement^>^ sectionData)
	: _sectionData(sectionData == nullptr ? gcnew List<OpenXmlElement^> : sectionData)
{
}

List<OpenXmlElement^>^ GostWordSection::GetSectionData()
{
	return _sectionData;
}

Document^ GostWordSection::CombineListSections(std::list<GostWordSection> sections)
{
	// TODO: how combine to 1 Document
	return gcnew Document();
}

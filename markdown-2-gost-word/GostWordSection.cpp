#include "GostWordSection.h"

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

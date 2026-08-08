#pragma once
#include "MdSection.h"

using namespace DocumentFormat::OpenXml;
using namespace System::Collections::Generic;

public ref class ClrParser
{
private:
	System::Object^ CreateObject(System::String^ name, System::String^ sectionText);
	void SetProperty(System::Object^ object, System::String^ name, System::String^ value);

public:
	// Creates one OpenXML tree. Every next rule item becomes a child of the
	// previous one, e.g. Paragraph; Run; Text {Value = %}.
	OpenXmlElement^ CreateObjectFromRule(System::String^ rule, MdSection* section);
};

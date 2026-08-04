#pragma once
#include "MdSection.h"

using namespace DocumentFormat::OpenXml;
using namespace System::Collections::Generic;

public ref class ClrParser
{
private:
	Object^ CreateObject(System::String^ name, String^ sectionText);

public:
	// 1. Extract a code from text (rules)
	void GetCodeFromRule(System::String^ rule);

	// 2. Create CLR objects from the list of objects
	List<OpenXmlElement^>^ CreateObjectsFromRule(System::String^ rule, MdSection* section);
};

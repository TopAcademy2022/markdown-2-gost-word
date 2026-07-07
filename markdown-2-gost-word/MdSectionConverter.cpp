#include "MdSectionConverter.h"

// 0. We need to obtain a list of rules.
// 0.1. Create an object with a set of rules
// 1. Convert each section of the MD file to each section of the Gost Word file
// 2. Add all sections to the list
// 3. Place the list in the GostWordSection class
void MdSectionConverter::ConvertToGostSections(std::list<MdSection*> sections)
{
	MdSectionRule mdRules;
	ClrParser^ parser = gcnew ClrParser();

	for (auto section : sections)
	{
		// For md section get clr objects
		std::list<std::string> names = mdRules.GetOXmlTypename(section->GetSectionType());
		System::String^ rule = names.empty()
			? System::String::Empty
			: gcnew System::String(names.front().c_str()); // Not true

		// Add clr gost xml objects to list
		_gostWordSection.push_back(new GostWordSection(parser->CreateObjectsFromRule(rule)));
	}
}

MdSectionConverter::MdSectionConverter(std::list<MdSection*> sections)
{
	this->ConvertToGostSections(sections);
}

MdSectionConverter::~MdSectionConverter()
{
	for (auto section : _gostWordSection)
	{
		delete section;
	}
}

XmlServiceStatus MdSectionConverter::SaveToGostWord()
{
	//// Maybe use OpenXmlService. Combine all sections (Run, Paragraph) to OpenXml Document
	//Document^ body = GostWordSection::CombineListSections(this->_gostWordSection);
	//// Use OpenXmlService for save document
	//int result = OpenXmlService_CreateDocument(L"result.docx", body);
	//// Return creating status
	//return static_cast<XmlServiceStatus>(result);

	return XmlServiceStatus::ok;
}

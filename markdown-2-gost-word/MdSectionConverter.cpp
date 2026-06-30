#include "MdSectionConverter.h"

void MdSectionConverter::ConvertToGostSections(std::list<MdSection*> sections)
{

}

MdSectionConverter::MdSectionConverter(std::list<MdSection*> sections)
{
	this->ConvertToGostSections(sections);
}

XmlServiceStatus MdSectionConverter::SaveToGostWord()
{
	return XmlServiceStatus();
}

#include "MdSectionConverter.h"

// 0. Необходимо получить список правил.
// 0.1. Создать объект с набором правил
// 1. Каждую секцию MD преобразовать в каждую секцию Gost Word
// 2. Все секции добавить в список
// 3. Список поместить в класс GostWordSection
void MdSectionConverter::ConvertToGostSections(std::list<MdSection*> sections)
{
	MdSectionRule mdRules;

	for (auto section : sections)
	{
		std::list<std::string> names = mdRules.GetOXmlTypename(section->GetSectionType());
		(void)names;

	}
}

MdSectionConverter::MdSectionConverter(std::list<MdSection*> sections)
{
	this->ConvertToGostSections(sections);
}

XmlServiceStatus MdSectionConverter::SaveToGostWord()
{
	return XmlServiceStatus();
}

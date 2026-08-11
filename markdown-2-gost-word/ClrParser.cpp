#include "ClrParser.h"

#include "MdSection.h"

using namespace DocumentFormat::OpenXml::Wordprocessing;
using namespace DocumentFormat::OpenXml;
using namespace System;
using namespace System::Reflection;
using namespace System::Collections::Generic;

namespace
{
	String^ FromUtf8(const std::string& value)
	{
		array<Byte>^ bytes = gcnew array<Byte>(static_cast<int>(value.size()));
		for (int index = 0; index < bytes->Length; ++index)
		{
			bytes[index] = static_cast<Byte>(value[index]);
		}

		return System::Text::Encoding::UTF8->GetString(bytes);
	}
}

void ClrParser::SetProperty(Object^ object, String^ name, String^ value)
{
	Type^ objectType = object->GetType();
	PropertyInfo^ property = objectType->GetProperty(name);

	// The compact rule language uses Value for the textual value of Text.
	if (property == nullptr && name == "Value"
		&& objectType == DocumentFormat::OpenXml::Wordprocessing::Text::typeid)
	{
		property = objectType->GetProperty("Text");
	}

	if (property == nullptr || !property->CanWrite)
	{
		throw gcnew Exception(
			"Unknown or read-only property '" + name + "' on " + objectType->FullName);
	}

	Object^ convertedValue;
	if (property->PropertyType == String::typeid)
	{
		convertedValue = value;
	}
	else
	{
		ConstructorInfo^ stringConstructor = property->PropertyType->GetConstructor(
			gcnew array<Type^> { String::typeid });

		convertedValue = stringConstructor != nullptr
			? stringConstructor->Invoke(gcnew array<Object^> { value })
			: Convert::ChangeType(value, property->PropertyType);
	}

	property->SetValue(object, convertedValue, nullptr);
}

Object^ ClrParser::CreateObject(String^ name, String^ sectionText)
{
	String^ definition = name->Trim();
	String^ properties = nullptr;
	int propertiesStart = definition->IndexOf('{');

	if (propertiesStart >= 0)
	{
		int propertiesEnd = definition->LastIndexOf('}');
		if (propertiesEnd <= propertiesStart)
		{
			throw gcnew FormatException("Invalid OpenXml rule item: " + definition);
		}

		properties = definition->Substring(
			propertiesStart + 1,
			propertiesEnd - propertiesStart - 1);
		definition = definition->Substring(0, propertiesStart)->Trim();
	}

    String^ fullName =
        "DocumentFormat.OpenXml.Wordprocessing." + definition;

    Type^ type = Type::GetType(
        fullName + ", DocumentFormat.OpenXml");

    if (type == nullptr)
        throw gcnew Exception("Unknown OpenXml type: " + definition);

	Object^ object = Activator::CreateInstance(type);
	if (properties != nullptr)
	{
		for each (String^ assignment in properties->Split(','))
		{
			array<String^>^ pair = assignment->Split(gcnew array<wchar_t> { '=' }, 2);
			if (pair->Length != 2)
			{
				throw gcnew FormatException("Invalid property assignment: " + assignment);
			}

			String^ value = pair[1]->Trim();
			if (value == "%")
			{
				value = sectionText;
			}
			else if (value->Length >= 2 && value[0] == '"' && value[value->Length - 1] == '"')
			{
				value = value->Substring(1, value->Length - 2);
			}

			SetProperty(object, pair[0]->Trim(), value);
		}
	}

	return object;
}

OpenXmlElement^ ClrParser::CreateObjectFromRule(
    String^ rule,
    MdSection* section)
{
	if (section == nullptr || String::IsNullOrWhiteSpace(rule))
		return nullptr;

	String^ sectionText = FromUtf8(section->GetContent());
    array<String^>^ partRule = rule->Split(';');
	OpenXmlElement^ root = nullptr;
	OpenXmlElement^ parent = nullptr;

    for each(String^ part in partRule)
    {
		if (!String::IsNullOrWhiteSpace(part))
        {
			OpenXmlElement^ object =
                safe_cast<OpenXmlElement^>(CreateObject(part->Trim(), sectionText));

			if (root == nullptr)
			{
				root = object;

				if (section->GetSectionType() == MdSectionType::title) {
					Paragraph^ paragraph = dynamic_cast<Paragraph^>(object);
					if (paragraph != nullptr) {
						ParagraphProperties^ pPr = paragraph->ParagraphProperties;
						if (pPr == nullptr) {
							pPr = gcnew ParagraphProperties();
							paragraph->PrependChild(pPr);
						}
						ParagraphStyleId^ styleId = gcnew ParagraphStyleId();
						styleId->Val = "Heading" + section->GetHeadingLevel();

						pPr->AppendChild(styleId);
					}
				}
			}
			else
			{
				OpenXmlCompositeElement^ compositeParent =
					dynamic_cast<OpenXmlCompositeElement^>(parent);
				if (compositeParent == nullptr)
				{
					throw gcnew FormatException(
						"OpenXml element cannot contain a child: " + parent->GetType()->Name);
				}

				compositeParent->AppendChild<OpenXmlElement^>(object);
			}

			parent = object;
        }
    }

	return root;
}

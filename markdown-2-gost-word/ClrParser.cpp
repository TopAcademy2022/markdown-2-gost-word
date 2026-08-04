#include "ClrParser.h"

#include "MdSection.h"

using namespace DocumentFormat::OpenXml::Wordprocessing;
using namespace DocumentFormat::OpenXml;
using namespace System;
using namespace System::Reflection;
using namespace System::Collections::Generic;

void ClrParser::GetCodeFromRule(System::String^ rule)
{
	(void)rule;
}

Object^ ClrParser::CreateObject(String^ name, String^ sectionText)
{
    if (name->Contains("{"))
    {
		// Cut {Value = %}
        // name = name->Substring();
    }

    String^ fullName =
        "DocumentFormat.OpenXml.Wordprocessing." + name;

    Type^ type = Type::GetType(
        fullName + ", DocumentFormat.OpenXml");

    if (name->Contains("{"))
    {
        PropertyInfo^ pi = type->GetProperty("InnerText");

        if (pi != nullptr)
        {
            Object^ value = Convert::ChangeType(sectionText, pi->PropertyType);
            Object^ obj = Activator::CreateInstance(type);
            pi->SetValue(obj, value, nullptr);

            return obj;
        }
    }

    if (type == nullptr)
        throw gcnew Exception("Unknown OpenXml type: " + name);

    return Activator::CreateInstance(type);
}

List<OpenXmlElement^>^ ClrParser::CreateObjectsFromRule(
    String^ rule,
    MdSection* section)
{
    List<OpenXmlElement^>^ result =
        gcnew List<OpenXmlElement^>();

    String^ sectionText = gcnew String(section->GetText().c_str());

    if (section == nullptr)
        return result;

    array<String^>^ partRule = rule->Split(';');

    for each(String^ part in partRule)
    {
        if (!String::IsNullOrEmpty(part))
        {
            OpenXmlElement^ obj =
                safe_cast<OpenXmlElement^>(CreateObject(part->Trim(), sectionText));

            if (obj != nullptr)
                result->Add(obj);
        }
    }

    return result;
}

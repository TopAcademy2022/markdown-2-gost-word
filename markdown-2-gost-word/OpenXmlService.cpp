#include "OpenXmlApi.h"
#include "OpenXmlService.h"

#include <vcclr.h>

#using "thirdparty\\openxml\\net46\\DocumentFormat.OpenXml.Framework.dll"
#using "thirdparty\\openxml\\net46\\DocumentFormat.OpenXml.dll"

using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace DocumentFormat::OpenXml;
using namespace DocumentFormat::OpenXml::Packaging;
using namespace DocumentFormat::OpenXml::Wordprocessing;

ref class OpenXmlAssemblyResolver abstract sealed
{
private:
    static bool installed = false;

public:
    static void Install()
    {
        if (installed)
        {
            return;
        }

        AppDomain::CurrentDomain->AssemblyResolve +=
            gcnew ResolveEventHandler(&OpenXmlAssemblyResolver::Resolve);
        installed = true;
    }

    static Assembly^ Resolve(Object^, ResolveEventArgs^ args)
    {
        AssemblyName^ requested = gcnew AssemblyName(args->Name);
        if (requested->Name != "DocumentFormat.OpenXml" &&
            requested->Name != "DocumentFormat.OpenXml.Framework")
        {
            return nullptr;
        }

        String^ assemblyDirectory = Path::GetDirectoryName(Assembly::GetExecutingAssembly()->Location);
        array<String^>^ candidates = gcnew array<String^>
        {
            Path::Combine(assemblyDirectory, requested->Name + ".dll"),
            Path::Combine(assemblyDirectory, "thirdparty\\openxml\\net46\\" + requested->Name + ".dll")
        };

        for each (String^ candidate in candidates)
        {
            if (File::Exists(candidate))
            {
                return Assembly::LoadFrom(candidate);
            }
        }

        return nullptr;
    }
};

namespace
{
    gcroot<String^> g_lastError;

    void SetLastError(String^ message)
    {
        g_lastError = message == nullptr ? String::Empty : message;
    }

    int CreateDocumentCore(String^ outputPath)
    {
        WordprocessingDocument^ document = WordprocessingDocument::Create(
            outputPath,
            WordprocessingDocumentType::Document);

        try
        {
            MainDocumentPart^ mainPart = document->AddMainDocumentPart();
            mainPart->Document = gcnew Document(
                gcnew Body(
                    gcnew Paragraph(
                        gcnew Run(
                            gcnew DocumentFormat::OpenXml::Wordprocessing::Text(
                                "Created by markdown-2-gost-word OpenXML API")))));

            mainPart->Document->Save();
        }
        finally
        {
            delete document;
        }

        return OPENXML_API_OK;
    }
}

int OpenXmlService_IsAvailable()
{
    OpenXmlAssemblyResolver::Install();
    SetLastError(String::Empty);
    return OPENXML_API_OK;
}

int OpenXmlService_CreateDocument(const wchar_t* outputPath)
{
    if (outputPath == nullptr || outputPath[0] == L'\0')
    {
        SetLastError("Output path is empty.");
        return OPENXML_API_INVALID_ARGUMENT;
    }

    try
    {
        OpenXmlAssemblyResolver::Install();
        SetLastError(String::Empty);
        return CreateDocumentCore(gcnew String(outputPath));
    }
    catch (Exception^ ex)
    {
        SetLastError(ex->ToString());
        return OPENXML_API_OPENXML_ERROR;
    }
    catch (...)
    {
        SetLastError("Unknown native exception.");
        return OPENXML_API_UNKNOWN_ERROR;
    }
}

int OpenXmlService_GetLastError(wchar_t* buffer, int bufferLength)
{
    if (buffer == nullptr || bufferLength <= 0)
    {
        return OPENXML_API_INVALID_ARGUMENT;
    }

    String^ lastError = g_lastError;
    if (lastError == nullptr)
    {
        lastError = String::Empty;
    }

    pin_ptr<const wchar_t> errorText = PtrToStringChars(lastError);
    int length = System::Math::Min(lastError->Length, bufferLength - 1);

    for (int i = 0; i < length; ++i)
    {
        buffer[i] = errorText[i];
    }

    buffer[length] = L'\0';
    return length;
}

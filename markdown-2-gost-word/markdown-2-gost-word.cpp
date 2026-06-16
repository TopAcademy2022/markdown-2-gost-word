#include "OpenXmlApi.h"
#include "OpenXmlService.h"

#include <iostream>
#include <string>
#include <fstream>

namespace
{
    void PrintMenu()
    {
        std::wcout << L"\nmarkdown-2-gost-word\n";
        std::wcout << L"1. Create test DOCX with OpenXML\n";
        std::wcout << L"2. Read md file\n";
        std::wcout << L"0. Exit\n";
        std::wcout << L"Select: ";
    }

    void PrintOpenXmlError()
    {
        constexpr int SIZE = 2048;
        wchar_t error[SIZE] = {};
        OpenXmlService_GetLastError(error, SIZE);

        if (error[0] != L'\0')
        {
            std::wcout << L"OpenXML error: " << error << L"\n";
        }
    }

    void CreateTestDocument()
    {
        std::wcout << L"Output .docx path: ";

        std::wstring outputPath;
        std::getline(std::wcin, outputPath);

        int result = OpenXmlService_CreateDocument(outputPath.c_str());
        if (result == XmlServiceStatus::ok)
        {
            std::wcout << L"Document created.\n";
            return;
        }

        std::wcout << L"Document was not created. Code: " << result << L"\n";
        PrintOpenXmlError();
    }
}

enum MdSectionType
{
	title,
    text
};

MdSectionType* GetSectionTypesFromText(std::string fullText)
{
    const char* full = fullText.c_str();
    MdSectionType* result = new MdSectionType[5];

	do
	{
        int i = 0;

        if (full[0] == '#')
        {
            result[i] = MdSectionType::title;
        }

        fullText = fullText.substr(fullText.find_first_of('\n'), fullText.length() - 1);
    } while (!fullText.empty());

    return result;
}

XmlServiceStatus ParseSections(MdSectionType* sections)
{
	if (MdSectionType::title)
    {
        // Parsing concrete section
	}

    return XmlServiceStatus::ok;
}

int main()
{
    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu();

        std::wstring command;
        std::getline(std::wcin, command);

        if (command == L"0")
            isRunning = false;
        if (command == L"1")
            CreateTestDocument();
        if (command == L"2") {

            // Read MD
            std::ifstream file("./example.md");
            int dataSize = 2048;
            char* fileData = new char[dataSize]();

            if (file.is_open())
            {
                file.read(fileData, dataSize);
            }

            MdSectionType* sections = GetSectionTypesFromText(fileData);
            if (sections != nullptr)
            {
                XmlServiceStatus result = ParseSections(sections);

                if (result == XmlServiceStatus::ok)
                {
                    std::wcout << L"Parsing has been complete.\n";
                }
            }
        }
    }
}

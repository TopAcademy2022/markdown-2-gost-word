#include "OpenXmlApi.h"
#include "OpenXmlService.h"

#include <iostream>
#include <string>
#include <fstream>

#include "MdSection.h"
#include "MdSectionConverter.h"
#include "MdSectionParser.h"

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
        constexpr int DEFAULT_BUFFER_SIZE = 2048;
        wchar_t error[DEFAULT_BUFFER_SIZE] = {};
        OpenXmlService_GetLastError(error, DEFAULT_BUFFER_SIZE);

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
        if (result == static_cast<int>(XmlServiceStatus::ok))
        {
            std::wcout << L"Document created.\n";
            return;
        }

        std::wcout << L"Document was not created. Code: " << result << L"\n";
        PrintOpenXmlError();
    }
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

            // Separate our text to logical sections
            // List with our logical sections
            std::list<MdSection*> sections = MdSectionParser::ParseText(fileData);

            // If list not empty
        	if (!sections.empty())
            {
                // Converting markdown logical sections to word sections
                MdSectionConverter converter(sections);
                // Save word sections to word file
                XmlServiceStatus result = converter.SaveToGostWord();

                if (result == XmlServiceStatus::ok)
                {
                    std::wcout << L"Parsing has been complete.\n";
                }
            }
        }
    }
}

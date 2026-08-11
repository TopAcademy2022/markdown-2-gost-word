#include "OpenXmlApi.h"
#include "OpenXmlService.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>

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
            const std::wstring inputPath = L"./example.md";

            // Read MD
            const std::wstring inputPath = L"./example.md";
            std::ifstream file(inputPath);

            // Ensure the input Markdown file was successfully opened
            if (!file.is_open())
            {
                std::wcout << L"Error: unable to open the file \"" << inputPath << L"\".\n";
                std::wcout << L"Make sure the file exists and is readable.\n";
                continue;
            }

            std::string fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            // Check the stream state after reading
            if (file.bad())
            {
                file.close();
                std::wcout << L"Error: failed to read the file \"" << inputPath << L"\".\n";
                continue;
            }

            file.close();

            // An empty input file must not be treated as a successful conversion
            if (fileData.empty())
            {
                std::wcout << L"Error: the input file \"" << inputPath << L"\" is empty.\n";
                continue;
            }

            // Separate our text to logical sections
            // List with our logical sections
            std::list<MdSection*> sections = MdSectionParser::ParseText(fileData);

            // If list is empty, the file does not contain supported sections
            if (sections.empty())
            {
                std::wcout << L"Error: no supported sections were found in the file \"" << inputPath << L"\".\n";
                std::wcout << L"The file must contain supported Markdown sections (e.g. headings, paragraphs).\n";
                continue;
            }

            // Converting markdown logical sections to word sections
            MdSectionConverter converter(sections);
            // Save word sections to word file
            XmlServiceStatus result = converter.SaveToGostWord(L"./result.docx");

            if (result == XmlServiceStatus::ok)
            {
                std::wcout << L"Parsing has been complete.\n";
            }
            else
            {
                std::wcout << L"Error: unable to save the result document. Code: " << static_cast<int>(result) << L"\n";
                PrintOpenXmlError();
            }

      for (MdSection* section : sections)
      {
        delete section;
      }
        }
    }
}
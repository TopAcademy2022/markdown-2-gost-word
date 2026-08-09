#include "OpenXmlApi.h"
#include "OpenXmlService.h"

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cwchar>
#include <cwctype>

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

    void PrintUsage()
    {
        std::wcout << L"Usage:\n";
        std::wcout << L"  markdown-2-gost-word <input.md> <output.docx>\n";
        std::wcout << L"  markdown-2-gost-word --help\n";
        std::wcout << L"\n";
        std::wcout << L"Convert a Markdown (.md) file to a GOST-styled Word (.docx) document.\n";
        std::wcout << L"\n";
        std::wcout << L"Options:\n";
        std::wcout << L"  -h, --help    Show this help message and exit.\n";
        std::wcout << L"\n";
        std::wcout << L"Examples:\n";
        std::wcout << L"  markdown-2-gost-word input.md output.docx\n";
        std::wcout << L"  markdown-2-gost-word \"docs/report.md\" \"out/report.docx\"\n";
    }

    bool EndsWithExtension(const std::wstring& path, const std::wstring& extension)
    {
        if (extension.size() > path.size())
        {
            return false;
        }

        std::wstring lowerPath(path.size(), L'\0');
        for (size_t i = 0; i < path.size(); ++i)
        {
            lowerPath[i] = std::towlower(path[i]);
        }

        return lowerPath.compare(lowerPath.size() - extension.size(), extension.size(), extension) == 0;
    }

    int ConvertMarkdownToGostWord(const std::wstring& inputPath, const std::wstring& outputPath)
    {
        // Read MD
        std::ifstream file(inputPath);

        // Ensure the input Markdown file was successfully opened
        if (!file.is_open())
        {
            std::wcout << L"Error: unable to open the file \"" << inputPath << L"\".\n";
            std::wcout << L"Make sure the file exists and is readable.\n";
            return 1;
        }

        std::string fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Check the stream state after reading
        if (file.bad())
        {
            file.close();
            std::wcout << L"Error: failed to read the file \"" << inputPath << L"\".\n";
            return 1;
        }

        file.close();

        // An empty input file must not be treated as a successful conversion
        if (fileData.empty())
        {
            std::wcout << L"Error: the input file \"" << inputPath << L"\" is empty.\n";
            return 1;
        }

        // Separate our text to logical sections
        // List with our logical sections
        std::list<MdSection*> sections = MdSectionParser::ParseText(fileData);

        // If list is empty, the file does not contain supported sections
        if (sections.empty())
        {
            std::wcout << L"Error: no supported sections were found in the file \"" << inputPath << L"\".\n";
            std::wcout << L"The file must contain supported Markdown sections (e.g. headings, paragraphs).\n";
            return 1;
        }

        // Converting markdown logical sections to word sections
        MdSectionConverter converter(sections);
        // Save word sections to word file
        XmlServiceStatus result = converter.SaveToGostWord(outputPath);

        if (result != XmlServiceStatus::ok)
        {
            std::wcout << L"Error: unable to save the result document. Code: " << static_cast<int>(result) << L"\n";
            PrintOpenXmlError();
            return 1;
        }

        std::wcout << L"Parsing has been complete.\n";
        return 0;
    }
}

int wmain(int argc, wchar_t* argv[])
{
    // No arguments: run the interactive menu
    if (argc == 1)
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
            if (command == L"2")
                ConvertMarkdownToGostWord(L"./example.md", L"./result.docx");
        }

        return 0;
    }

    // Help: print usage and exit successfully without creating a document
    if (argc == 2 && (std::wcscmp(argv[1], L"--help") == 0 || std::wcscmp(argv[1], L"-h") == 0))
    {
        PrintUsage();
        return 0;
    }

    // Only the two positional paths are accepted
    if (argc != 3)
    {
        std::wcout << L"Error: expected two arguments: <input.md> <output.docx>.\n\n";
        PrintUsage();
        return 2;
    }

    std::wstring inputPath = argv[1];
    std::wstring outputPath = argv[2];

    if (!EndsWithExtension(inputPath, L".md"))
    {
        std::wcout << L"Error: the input file \"" << inputPath << L"\" must have the .md extension.\n";
        return 2;
    }

    if (!EndsWithExtension(outputPath, L".docx"))
    {
        std::wcout << L"Error: the output file \"" << outputPath << L"\" must have the .docx extension.\n";
        return 2;
    }

    return ConvertMarkdownToGostWord(inputPath, outputPath);
}

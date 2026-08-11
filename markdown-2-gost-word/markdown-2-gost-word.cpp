#include "OpenXmlApi.h"
#include "OpenXmlService.h"

#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <cwctype>
#include <cwchar>

#include "MdSection.h"
#include "MdSectionConverter.h"
#include "MdSectionParser.h"

namespace
{
    constexpr int EXIT_SUCCESS_CODE = 0;
    constexpr int EXIT_FAILURE_CODE = 1;

    bool EndsWithIgnoreCase(const std::wstring& value, const std::wstring& suffix)
    {
        if (value.size() < suffix.size())
        {
            return false;
        }

        for (std::size_t i = 0; i < suffix.size(); ++i)
        {
            if (std::towlower(value[value.size() - suffix.size() + i]) != std::towlower(suffix[i]))
            {
                return false;
            }
        }

        return true;
    }

    void PrintUsage()
    {
        std::wcout << L"Usage: markdown-2-gost-word <input.md> <output.docx>\n";
        std::wcout << L"       markdown-2-gost-word --help\n";
        std::wcout << L"\n";
        std::wcout << L"Options:\n";
        std::wcout << L"  -h, --help  Print this help message\n";
        std::wcout << L"\n";
        std::wcout << L"Examples:\n";
        std::wcout << L"  markdown-2-gost-word input.md output.docx\n";
    }

    void PrintMenu()
    {
        std::wcout << L"\nmarkdown-2-gost-word\n";
        std::wcout << L"1. Create test DOCX with OpenXML\n";
        std::wcout << L"2. Convert markdown to GOST word document\n";
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

    bool ValidateExtensions(const std::wstring& inputPath, const std::wstring& outputPath)
    {
        bool valid = true;

        if (!EndsWithIgnoreCase(inputPath, L".md"))
        {
            std::wcout << L"Input file must have .md extension: " << inputPath << L"\n";
            valid = false;
        }

        if (!EndsWithIgnoreCase(outputPath, L".docx"))
        {
            std::wcout << L"Output file must have .docx extension: " << outputPath << L"\n";
            valid = false;
        }

        return valid;
    }

    bool ConvertMarkdownToGostWord(const std::wstring& inputPath, const std::wstring& outputPath)
    {
        if (!ValidateExtensions(inputPath, outputPath))
        {
            return false;
        }

        std::ifstream file(inputPath.c_str(), std::ios::binary);
        if (!file.is_open())
        {
            std::wcout << L"Could not open input file: " << inputPath << L"\n";
            return false;
        }

        std::string fileData(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());

        std::list<MdSection*> sections = MdSectionParser::ParseText(fileData);

        if (sections.empty())
        {
            std::wcout << L"No supported Markdown sections found in: " << inputPath << L"\n";
            return false;
        }

        MdSectionConverter converter(sections);
        XmlServiceStatus result = converter.SaveToGostWord(outputPath);

        for (MdSection* section : sections)
        {
            delete section;
        }

        if (result == XmlServiceStatus::ok)
        {
            std::wcout << L"Parsing has been complete.\n";
            return true;
        }

        std::wcout << L"Document was not created. Code: "
            << static_cast<int>(result) << L"\n";
        PrintOpenXmlError();
        return false;
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

    void RunInteractiveMenu()
    {
        bool isRunning = true;

        while (isRunning)
        {
            PrintMenu();

            std::wstring command;
            std::getline(std::wcin, command);

            if (command == L"0")
            {
                isRunning = false;
            }
            if (command == L"1")
            {
                CreateTestDocument();
            }
            if (command == L"2")
            {
                std::wcout << L"Input .md path: ";

                std::wstring inputPath;
                std::getline(std::wcin, inputPath);

                std::wcout << L"Output .docx path: ";

                std::wstring outputPath;
                std::getline(std::wcin, outputPath);

                ConvertMarkdownToGostWord(inputPath, outputPath);
            }
        }
    }
}

int wmain(int argc, wchar_t* argv[])
{
    if (argc == 1)
    {
        RunInteractiveMenu();
        return EXIT_SUCCESS_CODE;
    }

    if (argc == 2 &&
        (std::wcscmp(argv[1], L"--help") == 0 || std::wcscmp(argv[1], L"-h") == 0))
    {
        PrintUsage();
        return EXIT_SUCCESS_CODE;
    }

    if (argc == 3)
    {
        const std::wstring inputPath = argv[1];
        const std::wstring outputPath = argv[2];

        return ConvertMarkdownToGostWord(inputPath, outputPath)
            ? EXIT_SUCCESS_CODE
            : EXIT_FAILURE_CODE;
    }

    std::wcout << L"Error: expected <input.md> and <output.docx> arguments.\n\n";
    PrintUsage();
    return EXIT_FAILURE_CODE;
}

#include "OpenXmlApi.h"
#include "OpenXmlService.h"

#include <iostream>
#include <string>

namespace
{
    void PrintMenu()
    {
        std::wcout << L"\nmarkdown-2-gost-word\n";
        std::wcout << L"1. Create test DOCX with OpenXML\n";
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

int main()
{
    bool isRunning = true;

    while (isRunning)
    {
        PrintMenu();

        std::wstring command;
        std::getline(std::wcin, command);

        if (command == L"1")
        {
            CreateTestDocument();
        }
        else if (command == L"0")
        {
            isRunning = false;
        }
        else
        {
            std::wcout << L"Unknown menu item.\n";
        }
    }

    return 0;
}

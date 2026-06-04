#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream readFile("start.md");

    if (readFile.is_open())
    {
        std::string data;

        std::getline(readFile, data);


	    // 1. Very bad, not this example. Check title
        if (data.find("#") != std::string::npos)
        {
            std::cout << "This title" << std::endl;
        }
        else
        {
            std::cout << "This NOT title" << std::endl;
        }
    }
    else
    {
        std::cout << "File not opened!";
    }
   ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "ne udalos' otkrit' fail\n";
        return 1;
    }
    string line;
    int lineNumber = 1;
    while (getline(file, line)) {
        bool isCode = false;//Проверили всё, что хотели, и только один раз в конце принимаем решение
        if (line.find('{') != string::npos || line.find('}') != std::string::npos)
            isCode = true;
        if (line.find(';') != string::npos)
            isCode = true;
        if (line.find("int") != string::npos ||
            line.find("if") != string::npos ||
            line.find("else") != string::npos ||
            line.find("for") != string::npos ||
            line.find("while") != string::npos ||
            line.find("return") != string::npos)
            isCode = true;
        cout << "stroka " << lineNumber << ": ";
        if (isCode)
            cout << "kod - " << line << std::endl;
        else
            cout << "tekst - " << line << std::endl;
        lineNumber++;
    }
    file.close();
    return 0;
}
}

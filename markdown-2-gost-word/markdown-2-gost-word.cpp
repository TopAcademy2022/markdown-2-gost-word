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
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "ne udalos' otkrit' fail\n";
        return 1;
    }
    std::string line;
    int lineNumber = 1;
    while (getline(file, line)) {
        bool isCode = false;//Проверили всё, что хотели, и только один раз в конце принимаем решение
        if (line.find('{') != std::string::npos || line.find('}') != std::string::npos)
            isCode = true;
        if (line.find(';') != std::string::npos)
            isCode = true;
        if (line.find("int") != std::string::npos ||
            line.find("if") != std::string::npos ||
            line.find("else") != std::string::npos ||
            line.find("for") != std::string::npos ||
            line.find("while") != std::string::npos ||
            line.find("return") != std::string::npos)
            isCode = true;
        std::cout << "stroka " << lineNumber << ": ";
        if (isCode)
            std::cout << "kod - " << line << std::endl;
        else
            std::cout << "tekst - " << line << std::endl;
        lineNumber++;
    }
    file.close();
    return 0;
}


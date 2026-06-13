#include <iostream>
#include <fstream>
#include <string>
void checkMarkdown(const std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "не удалось открыть файл " << filename << std::endl;
        return;//не открывается
    }
    std::string line;
    std::getline(file, line);//ПЕРВУЮ строку
    file.close();
    bool isMarkdown = false;
    if (line.find('#') == 0)
        isMarkdown = true;
    if (line.find('-') == 0 || line.find('*') == 0 || line.find('+') == 0)
        isMarkdown = true;
    if (line.find('>') == 0)
        isMarkdown = true;
    if (line.find('[') != std::string::npos && line.find(']') != std::string::npos &&
        line.find('(') != std::string::npos && line.find(')') != std::string::npos)
        isMarkdown = true;
    if (line.find("**") != std::string::npos || line.find("__") != std::string::npos)
        isMarkdown = true;
    if (line.find('*') != std::string::npos || line.find('_') != std::string::npos) {
        if (line.find("**") == std::string::npos && line.find("__") == std::string::npos)
            isMarkdown = true;
    }
    if (line.find("---") != std::string::npos ||
        line.find("***") != std::string::npos ||
        line.find("___") != std::string::npos)
        isMarkdown = true;
    if (line.find("```") != std::string::npos)
        isMarkdown = true;
    std::cout << "Строка: " << line << std::endl;
    if (isMarkdown)
        std::cout << "Markdown" << std::endl;
    else
        std::cout << "не Markdown" << std::endl;
}
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

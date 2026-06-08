#include <iostream>
#include <fstream>
#include <string>

void func() {
    std::ifstream readFile("start.md");
    if (readFile.is_open())
    {
        std::string data;
        std::getline(readFile, data);
        if (data.find("0.") != std::string::npos ||
            data.find("1.") != std::string::npos ||
            data.find("2.") != std::string::npos ||
            data.find("3.") != std::string::npos ||
            data.find("4.") != std::string::npos ||
            data.find("5.") != std::string::npos ||
            data.find("6.") != std::string::npos ||
            data.find("7.") != std::string::npos ||
            data.find("8.") != std::string::npos ||
            data.find("9.") != std::string::npos)
        {
            std::cout << "This numeric list" << std::endl;
        }
        else
        {
            std::cout << "This NOT numeric list" << std::endl;
        }
    }
    else
    {
        std::cout << "File not opened!";
    }

}

int main()
{
    func();
}

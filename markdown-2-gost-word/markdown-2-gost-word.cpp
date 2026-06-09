#include <iostream>
#include <fstream>
#include <string>

bool IsMarkedList(std::string line) {
    bool res = false;
    if (line.find("- ") != std::string::npos) res = true;
    return res;
}

int main()
{
    std::ifstream readFile("start.md");

    if (readFile.is_open())
    {
        std::string data;

        std::getline(readFile, data);


        if (IsMarkedList(data))
        {
            std::cout << "This marked list" << std::endl;
        }
        else
        {
            std::cout << "This not marked list" << std::endl;
        }
    }
    else
    {
        std::cout << "File not opened!";
    }
}

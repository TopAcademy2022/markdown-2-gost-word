#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream readFile("Start.md");

    if (readFile.is_open())
    {
        std::string data;

        std::getline(readFile, data);


        // 1. Very bad, not this example. Check title
        if (data.find("- ") != std::string::npos)
        {
            std::cout << "This marked list" << std::endl;
        }
        else
        {
            std::cout << "This marked list" << std::endl;
        }
    }
    else
    {
        std::cout << "File not opened!";
    }
}

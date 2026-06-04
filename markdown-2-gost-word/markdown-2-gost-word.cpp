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
        if (isdigit(data[0]) && data.find(".") == 1)
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

#include <stdexcept>
#include <iostream>

#include "command.hpp"

// g++ aspects.cpp building.cpp city.cpp command.cpp dormitory.cpp main.cpp miner.cpp modern.cpp old.cpp programmer.cpp resident.cpp teacher.cpp test.cpp unemployed.cpp -o main.exe

int main()
{
    Command command;

    try
    {
        command.menu();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
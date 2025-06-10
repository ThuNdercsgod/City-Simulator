#include <stdexcept>
#include <iostream>

#include "menu.hpp"

// g++ aspects.cpp building.cpp city.cpp dormitory.cpp main.cpp menu.cpp miner.cpp modern.cpp old.cpp program.cpp programmer.cpp resident.cpp teacher.cpp unemployed.cpp -o main.exe

int main()
{
    Command command;

    try
    {
        command.menu();
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Memory allocation error!" << std::endl;
        return 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Memory allocation error!" << std::endl;
        return 1;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 3;
    }

    return 0;
}
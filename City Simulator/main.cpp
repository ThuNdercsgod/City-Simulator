#include <stdexcept>
#include <iostream>

#include "command.hpp"

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
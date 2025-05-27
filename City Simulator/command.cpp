#include <iostream>

#include "command.hpp"

void Command::menu() const
{
    int input;
    bool loop;

    do
    {
        loop = true;
        this->printMenu();
        std::cout << "Enter the number representing the command:" << std::endl;
        std::cin >> input;

        if (input == 0)
        {
            loop = false;
        }
        else
        {
            std::cerr << "Invalid input!" << std::endl;
        }
    } while (loop);
}

void Command::printMenu() const
{
    std::cout << "\n=== City Simulator ===\n"
              << "0. Exit\n"
              << std::endl;
}
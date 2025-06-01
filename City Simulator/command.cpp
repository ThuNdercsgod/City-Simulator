#include <iostream>

#include "command.hpp"
#include "test.hpp"

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

        switch (input)
        {
        case 0:
            loop = false;
            break;
        case 1:
            this->testsMenu();
            break;
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);
}

void Command::printMenu() const
{
    std::cout << "\n=== City Simulator ===\n"
              << "1. Tests\n"
              << "0. Exit\n"
              << std::endl;
}

void Command::testsMenu() const
{
    int input;
    bool loop;

    do
    {
        loop = true;
        this->printTestsMenu();
        std::cout << "Enter the number representing the command:" << std::endl;
        std::cin >> input;

        switch (input)
        {
        case 0:
            loop = false;
            break;
        case 1:
            this->buildingMenu();
            break;
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);
}

void Command::printTestsMenu() const
{
    std::cout << "\n=== City Simulator Tests ===\n"
              << "1. Building tests\n"
              << "0. Go back\n"
              << std::endl;
}

void Command::buildingMenu() const
{
    int input;
    bool loop;

    do
    {
        loop = true;
        this->printBuildingMenu();
        std::cout << "Enter the number representing the command:" << std::endl;
        std::cin >> input;

        switch (input)
        {
        case 0:
            loop = false;
            break;
        case 1:
            BuildingTest::basic();
            break;
        case 2:
            BuildingTest::residents();
            break;
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);
}

void Command::printBuildingMenu() const
{
    std::cout << "\n=== City Simulator Building Tests ===\n"
              << "1. Basic tests\n"
              << "2. Resident tests\n"
              << "0. Go back\n"
              << std::endl;
}
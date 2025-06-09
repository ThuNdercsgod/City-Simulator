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
            this->buildingTestMenu();
            break;
        case 2:
            this->residentTestMenu();
            break;
        case 3:
            this->cityTestMenu();
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
              << "2. Resident tests\n"
              << "3. City tests\n"
              << "0. Go back\n"
              << std::endl;
}

void Command::buildingTestMenu() const
{
    int input;
    bool loop;

    do
    {
        loop = true;
        this->printBuildingTestMenu();
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

void Command::printBuildingTestMenu() const
{
    std::cout << "\n=== City Simulator Building Tests ===\n"
              << "1. Basic tests\n"
              << "2. Resident tests\n"
              << "0. Go back\n"
              << std::endl;
}

void Command::residentTestMenu() const
{
    int input;
    bool loop;

    do
    {
        loop = true;
        this->printResidentTestMenu();
        std::cout << "Enter the number representing the command:" << std::endl;
        std::cin >> input;

        switch (input)
        {
        case 0:
            loop = false;
            break;
        case 1:
            ResidentTest::basic();
            break;
        case 2:
            ResidentTest::passDays();
            break;
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);
}

void Command::printResidentTestMenu() const
{
    std::cout << "\n=== City Simulator Resident Tests ===\n"
              << "1. Basic tests\n"
              << "2. Pass days tests\n"
              << "0. Go back\n"
              << std::endl;
}

void Command::cityTestMenu() const
{
    int input;
    bool loop;

    do
    {
        loop = true;
        this->printCityTestMenu();
        std::cout << "Enter the number representing the command:" << std::endl;
        std::cin >> input;

        switch (input)
        {
        case 0:
            loop = false;
            break;
        case 1:
            CityTest::basic();
            break;
        case 2:
            CityTest::passDays();
            break;
        case 3:
            CityTest::resident();
            break;
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);
}

void Command::printCityTestMenu() const
{
    std::cout << "\n=== City Simulator City Tests ===\n"
              << "1. Basic tests\n"
              << "2. Pass days test\n"
              << "3. Resident tests\n"
              << "0. Go back\n"
              << std::endl;
}
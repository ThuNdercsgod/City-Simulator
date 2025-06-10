#include <cstring>
#include <iostream>

#include "city.hpp"
#include "menu.hpp"
#include "program.hpp"

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
            this->program();
            break;
        case 2:
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
              << "1. City simulation\n"
              << "2. Tests\n"
              << "0. Exit\n"
              << std::endl;
}

void Command::program() const
{
    bool loop;
    int input;

    City *city = nullptr;
    Date *date = nullptr;

    // ! Remove when tests are complete
    date = new Date(1, 1, 2025);
    city = new City(3, 3, *date);

    do
    {
        loop = true;
        this->printProgram();
        std::cout << "Enter the number representing the command:" << std::endl;
        std::cin >> input;

        switch (input)
        {
        case 0:
            loop = false;
            break;
        case 1:
            Program::generate(city, date);
            break;
        case 2:
            Program::addResident(city);
            break;
        case 3:
            Program::removeResident(city);
            break;
        case 4:
            Program::stepOne(city, *date);
            break;
        case 5:
            Program::stepMultiple(city, *date);
            break;
        case 6:
            Program::infoBuilding(city);
            break;
        case 7:
            Program::infoResident(city);
            break;
        case 8:
            Program::info(city);
            break;
        // TODO save and load
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);

    if (city != nullptr)
    {
        delete city;
        city = nullptr;
    }
    if (date != nullptr)
    {
        delete date;
        date = nullptr;
    }
}

void Command::printProgram() const
{
    std::cout << "\n=== City Simulator ===\n"
              << "1. Generate City\n"
              << "2. Add Resident\n"
              << "3. Remove Resident\n"
              << "4. Step one day\n"
              << "5. Step <n> days\n"
              << "6. Info Building\n"
              << "7. Info Resident\n"
              << "8. Info City\n"
              << "9. Save City\n"
              << "10. Load City\n"
              << "0. Go back\n"
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
            Test::BuildingTest::basic();
            break;
        case 2:
            Test::BuildingTest::residents();
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
            Test::ResidentTest::basic();
            break;
        case 2:
            Test::ResidentTest::passDays();
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
            Test::CityTest::basic();
            break;
        case 2:
            Test::CityTest::passDays();
            break;
        case 3:
            Test::CityTest::resident();
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
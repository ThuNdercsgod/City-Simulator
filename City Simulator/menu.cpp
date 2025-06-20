#include <cstring>
#include <iostream>

#include "city.hpp"
#include "menu.hpp"
#include "program.hpp"

Command::~Command()
{
    if (city != nullptr)
    {
        delete city;
        city = nullptr;
    }
}

void Command::menu()
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

void Command::program()
{
    bool loop;
    int input;

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
            if (city != nullptr)
            {
                std::cerr << "City is already created" << std::endl;
                break;
            }
            this->city = Program::generate();
            break;
        case 2:
            Program::addResident(this->city);
            break;
        case 3:
            Program::removeResident(this->city);
            break;
        case 4:
            Program::stepOne(this->city);
            break;
        case 5:
            Program::stepMultiple(this->city);
            break;
        case 6:
            Program::infoBuilding(this->city);
            break;
        case 7:
            Program::infoResident(this->city);
            break;
        case 8:
            Program::info(this->city);
            break;
        case 9:
            Program::saveToFile(this->city);
            break;
        case 10:
            if (city != nullptr)
            {
                std::cerr << "City already exists!" << std::endl;
                break;
            }
            city = Program::loadFromFile();
            break;
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);
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
        case 4:
            this->simulationTestMenu();
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
              << "4. Simulation tests\n"
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

void Command::simulationTestMenu() const
{
    int input;
    bool loop;

    do
    {
        loop = true;
        this->printSimulationTestMenu();
        std::cout << "Enter the number representing the command:" << std::endl;
        std::cin >> input;

        switch (input)
        {
        case 0:
            loop = false;
            break;
        case 1:
            Test::SimulationTest::generate();
            break;
        case 2:
            Test::SimulationTest::resident();
            break;
        case 3:
            Test::SimulationTest::stepDays();
            break;
        default:
            std::cerr << "Invalid input!" << std::endl;
            break;
        }
    } while (loop);
}

void Command::printSimulationTestMenu() const
{
    std::cout << "\n=== City Simulator Simulation Tests ===\n"
              << "1. Generating tests\n"
              << "2. Resident tests\n"
              << "3. Step days tests\n"
              << "0. Go back\n"
              << std::endl;
}
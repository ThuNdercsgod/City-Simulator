#pragma once

class City;
class Date;

class Command
{
public:
    Command() {};
    Command(const Command &other) = delete;
    ~Command();

    void menu();
    void printMenu() const;

    void program();
    void printProgram() const;

    void testsMenu() const;
    void printTestsMenu() const;

    void buildingTestMenu() const;
    void printBuildingTestMenu() const;

    void residentTestMenu() const;
    void printResidentTestMenu() const;

    void cityTestMenu() const;
    void printCityTestMenu() const;

    City *city = nullptr;
};
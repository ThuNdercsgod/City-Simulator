#pragma once

#include <fstream>

#include "aspects.hpp"

class Building;

class Resident
{
public:
    Resident() = delete;
    Resident(const Resident &other) = delete; // Cannot have 2 identical Residents
    virtual ~Resident();

    static Resident *Factory(const char *name, Profession profession);
    static Resident *Factory(const char *name, Profession profession, unsigned happiness, unsigned money, unsigned health);

    Resident &operator=(const Resident &other) = delete; // Cannot have 2 identical Residents
    // bool operator==(const Resident &other) const;

    void saveToFile(std::ofstream &save) const;

    virtual void passOneDay(Date &currentDate) = 0;
    virtual void passMultipleDays(Date &currentDate, unsigned days) = 0;

    static Resident *createRandomResident(Location location, unsigned position);

    void print() const;
    void printStatus() const;
    void printCharacteristics() const;

    const char *getName() const;
    virtual const char *getProfession() const = 0;
    const Building *getBuilding() const;
    unsigned getHappiness() const;
    unsigned getMoney() const;
    unsigned getHealth() const;
    bool getIsAlive() const;

    void setBuilding(Building *building);

protected:
    Resident(const char *name);
    Resident(const char *name, unsigned happiness, unsigned money, unsigned health);

    static const char *createRandomName();

    void setHappiness(unsigned happiness);
    void setMoney(unsigned money);
    void setHealth(unsigned health);
    void setIsAlive(bool alive);

private:
    char *name;
    Building *building = nullptr;
    unsigned happiness = 100, money = 5000, health = 100;
    bool isAlive = true;
};
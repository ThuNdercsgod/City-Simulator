#pragma once

class Building;

enum class Profession
{
    Teacher = 0,
    Programmer = 1,
    Miner = 2,
    Unemployed = 3
};

class Resident
{
public:
    Resident() = delete;
    Resident(const Resident &other) = delete; // Cannot have 2 identical Residents
    virtual ~Resident();

    Resident &operator=(const Resident &other) = delete; // Cannot have 2 identical Residents
    bool operator==(const Resident &other) const;

    void print() const;
    virtual void printStatus() const = 0;
    void printProfession() const;

    const char *getName() const;
    unsigned getId() const;
    Profession getProfession() const;
    const Building *getBuilding() const;
    unsigned getHappiness() const;
    unsigned getMoney() const;
    unsigned getHealth() const;

    void setBuilding(Building *building);
    void setHappiness(unsigned happiness);
    void setMoney(unsigned money);
    void setHealth(unsigned health);

private:
    char *name;
    const unsigned id; // id = <x-coord> <y-coord> <pos in building>
    const Profession profession;
    Building *building = nullptr;
    unsigned happiness = 1, money = 1, health = 1;
    bool isAlive = true;
};

Resident *Factory(const char *name, unsigned id, Profession profession);
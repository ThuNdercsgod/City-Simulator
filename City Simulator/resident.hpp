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

    virtual void passOneDay(unsigned dayInSim) = 0;
    virtual void passMultipleDays(unsigned days, unsigned dayInSim) = 0;

    void print() const;
    void printStatus() const;

    const char *getName() const;
    unsigned getId() const;
    virtual const char *getProfession() const = 0;
    const Building *getBuilding() const;
    unsigned getHappiness() const;
    unsigned getMoney() const;
    unsigned getHealth() const;

    void setBuilding(Building *building);

protected:
    Resident(const char *name, unsigned id);

    void setHappiness(unsigned happiness);
    void setMoney(unsigned money);
    void setHealth(unsigned health);

private:
    char *name;
    const unsigned id; // id = <x-coord> <y-coord> <pos in building>
    Building *building = nullptr;
    unsigned happiness = 100, money = 5000, health = 100;
    bool isAlive = true;
};

Resident *Factory(const char *name, unsigned id, Profession profession);
// TODO
// Resident *Factory(const char *name, unsigned id, unsigned happiness, unsigned money, unsigned health);
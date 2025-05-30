#pragma once

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
private:
    const char *name;
    const unsigned id;
    Profession profession;
    unsigned happiness, money, health;
};
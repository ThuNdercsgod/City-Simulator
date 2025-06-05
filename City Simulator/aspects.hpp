#pragma once

struct Location
{
    Location(int x, int y);

    const int x;
    const int y;
};

enum class LocationType
{
    Normal = 0,
    Central = 1,
    Outer = 2
};

enum class BuildingType
{
    Modern = 0,
    Old = 1,
    Dormitory = 2
};

enum class Profession
{
    Teacher = 0,
    Programmer = 1,
    Miner = 2,
    Unemployed = 3
};

struct Date
{
public:
    Date(unsigned day, unsigned month, unsigned year);

    void passOneDay();
    void passMultipleDays(unsigned days);

    unsigned getDay() const;
    unsigned getMonth() const;
    unsigned getYear() const;

private:
    unsigned day, month, year;
};
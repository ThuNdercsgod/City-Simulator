#pragma once

#include "aspects.hpp"

class Building;

class Resident;

class City
{
public:
    City() = delete;
    City(unsigned length, unsigned width);
    City(const City &other) = delete;
    ~City();

    void addResident(Resident *resident) const;
    void removeResident(Resident *resident) const;
    bool checkResident(Resident *resident) const;
    // int checkResidentPosition(Resident *resident) const;

    void passOneDay(Date &currentDate) const;
    void passMultipleDays(Date &currentDate, unsigned days) const;

    void print() const;
    void printBuilding(unsigned x, unsigned y) const;
    void printResident(unsigned x, unsigned y, const char *name) const;

    unsigned getLength() const;
    unsigned getWidth() const;

private:
    const unsigned length;
    const unsigned width;
    Building **buildings = nullptr;
    Date startDate;
    Date currentDate;
};
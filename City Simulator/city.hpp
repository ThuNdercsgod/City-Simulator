#pragma once

#include "aspects.hpp"

class Building;

class Resident;

class City
{
public:
    City() = delete;
    City(unsigned length, unsigned width, Date date);
    City(const City &other) = delete;
    ~City();

    // TODO maybe also add them with Resident name
    void addResident(Resident *resident, Location location) const;
    void removeResident(Resident *resident, Location location) const;
    bool checkResident(Resident *resident, Location location) const;
    int checkResidentPosition(Resident *resident, Location location) const;

    void passOneDay(Date &currentDate) const;
    void passMultipleDays(Date &currentDate, unsigned days) const;

    // TODO Make it look cleaner
    void print() const;
    void printBuilding(Location location) const;
    void printResident(const char *name, Location location) const;

    unsigned getLength() const;
    unsigned getWidth() const;
    Location getCenterPoint() const;
    const Building *getBuilding(Location location) const;
    Date getStartDate() const;
    Date getCurrentDate() const;

private:
    void clearBuildings(unsigned length, unsigned width);

    const unsigned length;
    const unsigned width;
    const Location centerPoint;
    Building ***buildings = nullptr;
    const Date startDate;
    Date currentDate;
};
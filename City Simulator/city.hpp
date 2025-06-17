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

    City &operator=(const City &other) = delete;

    void saveToFile(const char *fileName) const;
    static City *loadFromFile(const char *fileName);

    void addResident(Resident *resident, Location location) const;
    void addResident(const char *name, Profession profession, unsigned happiness, unsigned money, unsigned health, Location location);
    void removeResident(Resident *resident, Location location) const;
    void removeResident(const char *name, Location location) const;
    bool checkResident(Resident *resident, Location location) const;
    bool checkResident(const char *name, Location location) const;
    int checkResidentPosition(Resident *resident, Location location) const;
    int checkResidentPosition(const char *name, Location location) const;

    void passOneDay();
    void passMultipleDays(unsigned days);

    void removeNotAliveResidents() const;

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
    City(unsigned length, unsigned width, Date startingDate, Date currentDate);
    void autoSave() const;
    void clearBuildings(unsigned length, unsigned width);

private:
    const unsigned length;
    const unsigned width;
    const Location centerPoint;
    Building ***buildings = nullptr;
    const Date startDate;
    Date currentDate;
};
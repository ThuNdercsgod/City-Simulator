#pragma once

#include <fstream>

#include "aspects.hpp"

class Resident;

class Building
{
public:
    Building() = delete;
    Building(const Building &other) = delete;
    virtual ~Building();

    Building &operator=(const Building &other) = delete;

    void saveToFile(std::ofstream &save) const;

    static Building *Factory(BuildingType buildingType, Location location, Location centerPoint, unsigned length, unsigned width);

    void addResident(Resident *resident);
    void removeResident(Resident *resident);
    void removeResident(const char *name);
    bool checkResident(const Resident *resident) const;
    bool checkResident(const char *name) const;
    int checkResidentPosition(const Resident *resident) const;
    int checkResidentPosition(const char *name) const;

    void passOneDay(Date &currentDate) const;
    void passMultipleDays(Date &currentDate, unsigned days) const;

    void removeNotAliveResidents();

    void print() const;
    void printStatus() const;

    virtual const char *getType() const = 0;
    double getRent() const;
    Location getLocation() const;
    LocationType getLocationType() const;
    const Resident *getResident(const char *name) const;
    unsigned getNumOfResidents() const;
    unsigned getCapacity() const;

protected:
    Building(Location location);

    bool checkName(const char *name, unsigned position) const;
    void createRandomResidents();

    void setRent(double rent);
    void setLocationType(LocationType locationType);
    void setNumOfResidents(unsigned numOfResidents);
    void setCapacity(unsigned capacity);

private:
    double rent = 0;
    Location location;
    LocationType locationType = LocationType::Normal;
    unsigned numOfResidents = 0;
    unsigned capacity = 0;
    Resident **residents = nullptr;
};

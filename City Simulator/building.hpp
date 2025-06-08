#pragma once

#include "aspects.hpp"

class Resident;

class Building
{
public:
    Building() = delete;
    Building(const Building &other) = delete;
    virtual ~Building();

    static Building *Factory(BuildingType buildingType, Location location, Location centerPoint, unsigned length, unsigned width);

    void addResident(Resident *resident);
    void removeResident(Resident *resident);
    bool checkResident(const Resident *resident) const;
    bool checkResident(const char *name) const;
    int checkResidentPosition(const Resident *resident) const;
    int checkResidentPosition(const char *name) const;

    void passOneDay(Date &currentDate) const;
    void passMultipleDays(Date &currentDate, unsigned days) const;

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

    void createRandomResidents();

    void setRent(double rent);
    void setLocationType(LocationType locationType);
    void setCapacity(unsigned capacity);

private:
    double rent = 0;
    Location location;
    LocationType locationType = LocationType::Normal;
    Resident **residents = nullptr;
    unsigned numOfResidents = 0;
    unsigned capacity = 0;
};

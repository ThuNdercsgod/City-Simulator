#pragma once

#include "aspects.hpp"

class Resident;

class Building
{
public:
    Building() = delete;
    Building(const Building &other) = delete;
    virtual ~Building();

    void addResident(Resident *resident);
    void removeResident(Resident *resident);
    bool checkResident(const Resident *resident) const;
    bool checkResident(const char *name) const;
    int checkResidentPosition(const Resident *resident) const;
    int checkResidentPosition(const char *name) const;

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

Building *Factory(BuildingType buildingType, Location location, Location centerPoint, unsigned length, unsigned width);
#pragma once

class Resident;

enum class Location
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

class Building
{
public:
    Building() = default;
    Building(const Building &other) = default;

    // TODO make them in the base class
    void addResident(Resident *resident);
    void removeResident(int id);
    bool checkResident(int id) const;

    virtual Building *clone() const = 0;
    void print() const;
    virtual void printStatus() const = 0;

    virtual const char *getType() const = 0;
    double getRent() const;
    Location getLocation() const;
    unsigned getNumOfResidents() const;

protected:
    void setRent(double rent);
    void setLocation(Location location);

private:
    // TODO Maybe Location should be determined when constructing the object
    // TODO and based on the coordinates of the Building
    double rent = 0;
    Location location = Location::Normal;
    Resident **residents = nullptr;
    unsigned numOfResidents = 0;
};

Building *Factory(BuildingType type, Location location);
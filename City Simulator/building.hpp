#pragma once

class Resident;

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

class Building
{
public:
    Building() = delete;
    Building(const Building &other) = delete;
    virtual ~Building();

    void addResident(Resident *resident);
    void removeResident(Resident *resident);
    bool checkResident(const Resident *resident) const;
    int checkResidentPosition(const Resident *resident) const;

    void print() const;
    void printStatus() const;

    virtual const char *getType() const = 0;
    double getRent() const;
    LocationType getLocationType() const;
    unsigned getNumOfResidents() const;

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

Building *Factory(BuildingType buildingType, Location location, Location centerPoint, unsigned width, unsigned length);
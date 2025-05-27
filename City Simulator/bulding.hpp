#pragma once

class Resident;

class Building
{
public:
    Building() = default;
    Building(const Building &other) = delete;

    // TODO make them in the base class
    void addResident(Resident *resident);
    void removeResident(int id);
    bool checkResident(int id) const;

    virtual const char *getType() const = 0;

    Location getLocation() const;
    unsigned getNumOfResidents() const;

protected:
    void setLocation(Location location);

private:
    //! Maybe Location should be determined when constructing the object
    //! and based on the coordinates of the Building
    Location location = Location::Normal;
    Resident **residents = nullptr;
    unsigned numOfResidents = 0;
};

enum Location
{
    Normal = 0,
    Central = 1,
    Outer = 2
};
#pragma once

#include "building.hpp"

class Modern : public Building
{
public:
    Modern() = delete;
    Modern(Location location, Location centerPoint, unsigned width, unsigned length);
    // No copy constructor, because it will copy the Residents
    Modern(const Modern &other) = delete;

    void printStatus() const override;

    const char *getType() const override;
    double getRent() const;

private:
    void setRent(LocationType locationType);

    // Default rent, without location
    double rent = 1000;
};
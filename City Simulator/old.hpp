#pragma once

#include "building.hpp"

class Old : public Building
{
public:
    Old() = delete;
    Old(Location location, Location centerPoint, unsigned width, unsigned length);
    // No copy constructor, because it will copy the Residents
    Old(const Old &other) = delete;

    void printStatus() const override;

    const char *getType() const override;
    double getRent() const;

private:
    void setRent(LocationType locationType);

    // Default rent, without location
    double rent = 500;
};
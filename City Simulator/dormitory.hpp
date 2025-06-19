#pragma once

#include "building.hpp"

class Dormitory : public Building
{
public:
    Dormitory() = delete;
    Dormitory(Location location, Location centerPoint, unsigned length, unsigned width);
    Dormitory(std::ifstream &load, Location location, LocationType locationType, unsigned numOfResidents);
    // No copy constructor, because it will copy the Residents
    Dormitory(const Dormitory &other) = delete;

    Dormitory &operator=(const Dormitory &other) = delete;

    const char *getType() const override;
};
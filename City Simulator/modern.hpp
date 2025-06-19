#pragma once

#include "building.hpp"

class Modern : public Building
{
public:
    Modern() = delete;
    Modern(Location location, Location centerPoint, unsigned length, unsigned width);
    Modern(std::ifstream &load, Location location, LocationType locationType, unsigned numOfResidents);
    // No copy constructor, because it will copy the Residents
    Modern(const Modern &other) = delete;

    Modern &operator=(const Modern &other) = delete;

    const char *getType() const override;
};
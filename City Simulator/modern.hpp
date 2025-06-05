#pragma once

#include "building.hpp"

class Modern : public Building
{
public:
    Modern() = delete;
    Modern(Location location, Location centerPoint, unsigned length, unsigned width);
    // No copy constructor, because it will copy the Residents
    Modern(const Modern &other) = delete;

    const char *getType() const override;
};
#pragma once

#include "building.hpp"

class Old : public Building
{
public:
    Old() = delete;
    Old(Location location, Location centerPoint, unsigned length, unsigned width);
    // No copy constructor, because it will copy the Residents
    Old(const Old &other) = delete;

    const char *getType() const override;
};
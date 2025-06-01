#pragma once

#include "building.hpp"

class Old : public Building
{
public:
    Old() = delete;
    Old(Location location);
    // No copy constructor, because it will copy the Residents
    Old(const Old &other) = delete;

    void printStatus() const override;

    const char *getType() const override;
    double getRent() const;

private:
    void setRent(Location location);

    // Default rent, without location
    double rent = 500;
};
#pragma once

#include "building.hpp"

class Dormitory : public Building
{
public:
    Dormitory() = delete;
    Dormitory(Location location);
    // No copy constructor, because it will copy the Residents
    Dormitory(const Dormitory &other) = delete;

    void printStatus() const override;

    const char *getType() const override;
    double getRent() const;

private:
    void setRent(Location location);

    // Default rent, without location
    double rent = 40;
};
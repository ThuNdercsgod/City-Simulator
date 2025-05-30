#pragma once

#include "building.hpp"

class Dormitory : public Building
{
public:
    Dormitory() = delete;
    Dormitory(Location location);

    Building *clone() const override;
    void printStatus() const override;

    const char *getType() const override;
    double getRent() const;

private:
    Dormitory(const Dormitory &other) = default;

    void setRent(Location location);

    // Default rent, without location
    double rent = 40;
};
#pragma once

#include "building.hpp"

class Modern : public Building
{
public:
    Modern() = delete;
    Modern(Location location);

    Building *clone() const override;
    void printStatus() const override;

    const char *getType() const override;
    double getRent() const;

private:
    Modern(const Modern &other) = default;

    void setRent(Location location);

    // Default rent, without location
    double rent = 1000;
};
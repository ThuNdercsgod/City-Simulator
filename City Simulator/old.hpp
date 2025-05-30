#pragma once

#include "building.hpp"

class Old : public Building
{
public:
    Old() = delete;
    Old(Location location);

    Building *clone() const override;
    void printStatus() const override;

    const char *getType() const override;
    double getRent() const;

private:
    Old(const Old &other) = default;

    void setRent(Location location);

    // Default rent, without location
    double rent = 500;
};
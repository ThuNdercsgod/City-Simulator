#pragma once

#include "bulding.hpp"

class Modern : public Building
{
public:
    Modern() = delete;
    Modern(Location location);
    Modern(const Modern &other) = delete;

    const char *getType() const override;
    double getRent() const;

private:
    void setRent(Location location);

    double rent = 1000;
};
#pragma once

#include "resident.hpp"

class Programmer : public Resident
{
public:
    Programmer() = delete;
    Programmer(const char *name, unsigned id);
    Programmer(const Programmer &other) = delete;

    Programmer &operator=(const Programmer &other) = delete;

    void passOneDay(unsigned dayInSim) override;
    void passMultipleDays(unsigned days, unsigned dayInSim) override;

    const char *getProfession() const override;
};
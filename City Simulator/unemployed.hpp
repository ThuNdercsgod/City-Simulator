#pragma once

#include "resident.hpp"

class Unemployed : public Resident
{
public:
    Unemployed() = delete;
    Unemployed(const char *name, unsigned id);
    Unemployed(const Unemployed &other) = delete;

    Unemployed &operator=(const Unemployed &other) = delete;

    void passOneDay(unsigned dayInSim) override;
    void passMultipleDays(unsigned days, unsigned dayInSim) override;

    const char *getProfession() const override;
};
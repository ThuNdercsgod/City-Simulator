#pragma once

#include "resident.hpp"

class Unemployed : public Resident
{
public:
    Unemployed() = delete;
    Unemployed(const char *name);
    Unemployed(const char *name, Profession profession, unsigned happiness, unsigned money, unsigned health);
    Unemployed(const Unemployed &other) = delete;

    Unemployed &operator=(const Unemployed &other) = delete;

    void passOneDay(Date &currentDate) override;
    void passMultipleDays(Date &currentDate, unsigned days) override;

    const char *getProfession() const override;
};
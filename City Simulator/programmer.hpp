#pragma once

#include "resident.hpp"

class Programmer : public Resident
{
public:
    Programmer() = delete;
    Programmer(const char *name, unsigned id);
    Programmer(const Programmer &other) = delete;

    Programmer &operator=(const Programmer &other) = delete;

    void passOneDay(Date &currentDate) override;
    void passMultipleDays(Date &currentDate, unsigned days) override;

    const char *getProfession() const override;
};
#pragma once

#include "resident.hpp"

class Teacher : public Resident
{
public:
    Teacher() = delete;
    Teacher(const char *name);
    Teacher(const char *name, unsigned happiness, unsigned money, unsigned health);
    Teacher(const Teacher &other) = delete;

    Teacher &operator=(const Teacher &other) = delete;

    void passOneDay(Date &currentDate) override;
    void passMultipleDays(Date &currentDate, unsigned days) override;

    const char *getProfession() const override;
};
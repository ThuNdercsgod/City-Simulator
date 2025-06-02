#pragma once

#include "resident.hpp"

class Teacher : public Resident
{
public:
    Teacher() = delete;
    Teacher(const char *name, unsigned id);
    Teacher(const Teacher &other) = delete;

    Teacher &operator=(const Teacher &other) = delete;

    void passOneDay(unsigned dayInSim) override;
    void passMultipleDays(unsigned days, unsigned dayInSim) override;

    const char *getProfession() const override;
};
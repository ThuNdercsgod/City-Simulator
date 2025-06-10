#pragma once

#include "resident.hpp"

class Miner : public Resident
{
public:
    Miner() = delete;
    Miner(const char *name);
    Miner(const char *name, Profession profession, unsigned happiness, unsigned money, unsigned health);
    Miner(const Miner &other) = delete;

    Miner &operator=(const Miner &other) = delete;

    void passOneDay(Date &currentDate) override;
    void passMultipleDays(Date &currentDate, unsigned days) override;

    const char *getProfession() const override;
};
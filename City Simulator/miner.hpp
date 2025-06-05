#pragma once

#include "resident.hpp"

class Miner : public Resident
{
public:
    Miner() = delete;
    Miner(const char *name, unsigned id);
    Miner(const Miner &other) = delete;

    Miner &operator=(const Miner &other) = delete;

    void passOneDay(Date &currentDate) override;
    void passMultipleDays(Date &currentDate, unsigned days) override;

    const char *getProfession() const override;
};
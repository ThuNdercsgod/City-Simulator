#pragma once

#include "resident.hpp"

class Miner : public Resident
{
public:
    Miner() = delete;
    Miner(const char *name, unsigned id);
    Miner(const Miner &other) = delete;

    Miner &operator=(const Miner &other) = delete;

    void passOneDay(unsigned dayInSim) override;
    void passMultipleDays(unsigned days, unsigned dayInSim) override;

    const char *getProfession() const override;
};
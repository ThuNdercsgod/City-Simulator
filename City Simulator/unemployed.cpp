#include "unemployed.hpp"

#include "building.hpp"

Unemployed::Unemployed(const char *name)
    : Resident(name) {}

Unemployed::Unemployed(const char *name, unsigned happiness, unsigned money, unsigned health)
    : Resident(name, happiness, money, health) {}

void Unemployed::passOneDay(Date &currentDate)
{
    // Food
    if (this->getMoney() < 50)
    {
        this->setMoney(0);
        this->setHealth(0);
        this->setHappiness(0);
        this->setIsAlive(false);
        return;
    }
    else
    {
        this->setMoney(this->getMoney() - 50);
    }
    // Profession cost
    this->setHealth(((this->getHealth() - 1) > 0) ? (this->getHealth() - 1) : 0);

    // The 1st day of every month
    if (currentDate.getDay() == 1)
    {
        int income = 0;

        if (this->getBuilding() != nullptr &&
            this->getMoney() < this->getBuilding()->getRent())
        {
            this->setMoney(0);
            this->setHappiness(0);
        }
        else if (this->getBuilding() != nullptr)
        {
            this->setMoney(this->getMoney() + income - this->getBuilding()->getRent());
        }
        else
        {
            this->setMoney(this->getMoney() + income);
        }
    }

    if (this->getHappiness() == 0 ||
        this->getMoney() == 0 ||
        this->getHealth() == 0)
    {
        this->setMoney(0);
        this->setHealth(0);
        this->setHappiness(0);
        this->setIsAlive(false);
    }
}

void Unemployed::passMultipleDays(Date &currentDate, unsigned days)
{
    if (days == 0)
    {
        return;
    }
    for (unsigned i = 0; i < days; i++)
    {
        if (this->getIsAlive() == false)
        {
            break;
        }
        this->passOneDay(currentDate);
    }
}

const char *Unemployed::getProfession() const
{
    return "Unemployed";
}
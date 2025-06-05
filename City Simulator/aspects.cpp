#include <stdexcept>

#include "aspects.hpp"

Location::Location(int x, int y)
    : x(x), y(y) {}

// The starting year is 1900
Date::Date(unsigned day, unsigned month, unsigned year)
{
    switch (month)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        if (day > 30)
        {
            throw std::invalid_argument("Invalid Date format!");
        }
        break;
    case 2:
        // Leap year check
        if (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) &&
            (day > 29))
        {

            throw std::invalid_argument("Invalid Date format!");
        }
        else if (day > 28)
        {
            throw std::invalid_argument("Invalid Date format!");
        }
        break;
    default:
        if (day > 31 || month > 12 || year < 1900)
        {
            throw std::invalid_argument("Invalid Date format!");
        }
        break;
    }

    this->day = day;
    this->month = month;
    this->year = year;
}

void Date::passOneDay()
{
    switch (this->month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (this->day < 31)
        {
            this->day++;
        }
        else
        {
            this->day = 1;
            this->month = 1;
            this->year++;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (this->day < 30)
        {
            this->day++;
        }
        else
        {
            this->day = 1;
            this->month++;
        }
        break;
    case 2:
        if (((this->year % 4 == 0 && this->year % 100 != 0) || (this->year % 400 == 0)))
        {

            if (this->day < 29)
            {
                this->day++;
            }
            else
            {
                this->day = 1;
                this->month++;
            }
        }
        else
        {
            if (this->day < 28)
            {
                this->day++;
            }
            else
            {
                this->day = 1;
                this->month++;
            }
        }
        break;
    }
}

void Date::passMultipleDays(unsigned days)
{
    for (unsigned i = 0; i < days; i++)
    {
        this->passOneDay();
    }
}

unsigned Date::getDay() const
{
    return this->day;
}

unsigned Date::getMonth() const
{
    return this->month;
}

unsigned Date::getYear() const
{
    return this->year;
}
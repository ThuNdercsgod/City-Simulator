#pragma once

#include "aspects.hpp"

class City;

namespace Program
{
    void generate(City *city, Date *date);

    void addResident(City *city);
    void removeResident(City *city);

    void stepOne(City *city, Date &currentDate);
    void stepMultiple(City *city, Date &currentDate);

    void info(City *city);
    void infoBuilding(City *city);
    void infoResident(City *city);
};

namespace Test
{
    namespace BuildingTest
    {
        void basic();
        void residents();
    }

    namespace ResidentTest
    {
        void basic();
        void passDays();
    }

    namespace CityTest
    {
        void basic();
        void passDays();
        void resident();
    };
};

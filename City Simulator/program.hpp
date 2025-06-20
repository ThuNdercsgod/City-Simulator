#pragma once

#include "aspects.hpp"

class City;

namespace Program
{
    City *generate();

    void addResident(City *city);
    void removeResident(City *city);

    void stepOne(City *city);
    void stepMultiple(City *city);

    void info(City *city);
    void infoBuilding(City *city);
    void infoResident(City *city);

    void saveToFile(City *city);
    City *loadFromFile();
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

    namespace SimulationTest
    {
        void generate();
        void resident();
        void stepDays();
    };
};
#include "Residential.h"

Residential::Residential(City &city, int population) : Building(city)
{
    this->population = population;
}

Building::Category Residential::get_category() const
{
    return this->category;
}

int Residential::get_population_growth_rate_contribution() const
{
    return -get_population();
}

void Residential::increase_population(int population)
{
    if (get_population() + population > get_max_population())
    {
        this->population = get_max_population();
    }
    else if (get_population() + population < 0)
    {
        this->population = 0;
    }
    else
    {
        this->population = get_population() + population;
    }
}

int Residential::get_revenue() const {}
int Residential::get_population() const {}
int Residential::get_max_population() const {}
int Residential::get_population_growth() const {}

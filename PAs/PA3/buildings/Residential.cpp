#include "Residential.h"

Residential::Residential(City &city, int population) : Building(city), population(population) {}

Building::Category Residential::get_category() const
{
    return Building::Category::RESIDENTIAL;
}

int Residential::get_population() const { return population; }

int Residential::get_population_growth_rate_contribution() const { return -get_population(); }

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

/*dummy implementation*/
int Residential::get_revenue() const { return 0; }
int Residential::get_max_population() const { return 0; }
int Residential::get_population_growth() const { return 0; }

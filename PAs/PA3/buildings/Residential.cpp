#include "Residential.h"

Residential::Residential(City &city, int population) : Building(city) { this->population = 0; }

Building::Category Residential::get_category() const
{
    return Building::Category::RESIDENTIAL;
}

int Residential::get_population() const { return this->population; }

int Residential::get_population_growth_rate_contribution() const { return -this->population; }

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
void Residential::increase_population(int population) { population = 0; }

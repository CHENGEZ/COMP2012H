#include "buildings/Revenue.h"

Revenue::Revenue(City &city) : Building(city) {}

Building::Category Revenue::get_category() const
{
    return this->category;
}

void Revenue::increase_population(int population) {}

int Revenue::get_revenue() const {}
int Revenue::get_population() const {}
int Revenue::get_max_population() const {}
int Revenue::get_population_growth() const {}
int Revenue::get_population_growth_rate_contribution() const {}

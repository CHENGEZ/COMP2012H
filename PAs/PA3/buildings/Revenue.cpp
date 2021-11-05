#include "Revenue.h"

Revenue::Revenue(City &city) : Building(city) {}

Building::Category Revenue::get_category() const
{
    return Building::Category::REVENUE;
}

void Revenue::increase_population(int population) { population = 0; }
int Revenue::get_revenue() const { return 0; }
int Revenue::get_population() const { return 0; }
int Revenue::get_max_population() const { return 0; }
int Revenue::get_population_growth() const { return 0; }
int Revenue::get_population_growth_rate_contribution() const { return 0; }
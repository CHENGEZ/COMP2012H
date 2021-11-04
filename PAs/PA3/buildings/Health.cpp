#include "buildings/Health.h"
#include "City.h"

Health::Health(City &city) : Building(city) {}

Building::Category Health::get_category() const
{
    return this->category;
}

void Health::increase_population(int population) {}

int Health::get_revenue() const {}
int Health::get_population() const {}
int Health::get_max_population() const {}
int Health::get_population_growth() const {}
int Health::get_population_growth_rate_contribution() const {}

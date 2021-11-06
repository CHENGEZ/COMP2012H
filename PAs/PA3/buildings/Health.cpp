#include "Health.h"

Health::Health(City &city) : Building(city) {}

Building::Category Health::get_category() const
{
    return Building::Category::HEALTH;
}

void Health::increase_population(int population) { population += 0; }
int Health::get_revenue() const { return 0; }
int Health::get_population() const { return 0; }
int Health::get_max_population() const { return 0; }
int Health::get_population_growth() const { return 0; }
int Health::get_population_growth_rate_contribution() const { return 0; }

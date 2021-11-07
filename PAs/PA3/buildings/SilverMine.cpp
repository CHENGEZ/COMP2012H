// #include "SilverMine.h"
#include "../City.h"

using namespace std;

SilverMine::SilverMine(City &city) : Revenue(city) {}

Building::Type SilverMine::get_type() const
{
    return Building::Type::SILVER_MINE;
}

int SilverMine::get_cost() const
{
    return this->cost;
}

std::string SilverMine::get_long_information() const
{
    return SILVER_HEADER + '\n' +
           SILVER_1_1 + std::to_string(Building::number_neighboring_population() + city.get_population()) + '\n' + SILVER_2_1 + '\n';
}

std::string SilverMine::get_short_information() const
{
    return SILVER_HEADER + '\n' +
           SILVER_1_1 + std::to_string(Building::number_neighboring_population() + city.get_population()) + '\n';
}

int SilverMine::get_revenue() const
{
    return Building::number_neighboring_population() + city.get_population();
}

int SilverMine::get_population() const { return 0; }
int SilverMine::get_max_population() const { return 0; }
int SilverMine::get_population_growth() const { return 0; }
int SilverMine::get_population_growth_rate_contribution() const { return 0; }
void SilverMine::increase_population(int population) { population += 0; }

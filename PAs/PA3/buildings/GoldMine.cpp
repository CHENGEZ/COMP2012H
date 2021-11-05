// #include "GoldMine.h"
#include "../City.h"

using namespace std;

GoldMine::GoldMine(City &city) : Revenue(city) {}

Building::Type GoldMine::get_type() const
{
    return Building::Type::GOLD_MINE;
}

int GoldMine::get_cost() const
{
    return this->cost;
}

std::string GoldMine::get_long_information() const
{
    return GOLD_HEADER + '\n' +
           GOLD_1_1 + std::to_string(2 * (Building::number_neighboring_population() + city.get_population())) + '\n' +
           GOLD_2_1 + '\n';
}

std::string GoldMine::get_short_information() const
{
    return GOLD_HEADER + '\n' +
           GOLD_1_1 + std::to_string(2 * (Building::number_neighboring_population() + city.get_population())) + '\n';
}

int GoldMine::get_revenue() const
{
    return 2 * (Building::number_neighboring_population() + city.get_population());
}

int GoldMine::get_population() const { return 0; }
int GoldMine::get_max_population() const { return 0; }
int GoldMine::get_population_growth() const { return 0; }
int GoldMine::get_population_growth_rate_contribution() const { return 0; }
void GoldMine::increase_population(int population) { population = 0; }


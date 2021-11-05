#include "House.h"
#include "../City.h"

using namespace std;

House::House(City &city, int population) : Residential(city, population) {}

Building::Type House::get_type() const
{
    return Building::Type::HOUSE;
}

int House::get_cost() const
{
    return this->cost;
}

std::string House::get_long_information() const
{
    return HOUSE_HEADER + '\n' + HOUSE_1_1 + std::to_string(get_population()) +
           '\n' + HOUSE_2_1 + std::to_string(get_max_population()) + '\n' + HOUSE_3_1 + '\n' + HOUSE_4_1 + std::to_string(get_population_growth_rate_contribution()) + '\n' + HOUSE_5_1 +
           '\n' + HOUSE_6_1 + std::to_string(get_population_growth()) + HOUSE_6_2 + std::to_string(get_max_population() - get_population()) + HOUSE_6_3 + '\n' + HOUSE_7_1 + '\n';
}

std::string House::get_short_information() const
{
    return HOUSE_HEADER + '\n' + HOUSE_1_1 +
           std::to_string(Building::get_population()) + '\n' + HOUSE_2_1 + std::to_string(Building::get_max_population()) +
           '\n' + HOUSE_4_1 + std::to_string(Building::get_population_growth_rate_contribution()) + '\n' +
           HOUSE_6_1 + std::to_string(Building::get_population_growth()) + '\n';
}

int House::get_revenue() const { return 0; }
int House::get_max_population() const { return 50 * (1 + Building::number_neighboring_residential_buildings()); }
int House::get_population_growth() const
{
    return city.get_population_growth_rate() * (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10 <
                   Building::get_max_population() - Building::get_population()
               ? city.get_population_growth_rate() *
                     (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10
               : Building::get_max_population() - Building::get_population();
}

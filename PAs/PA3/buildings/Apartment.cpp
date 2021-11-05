#include "Apartment.h"
#include "../City.h"
using namespace std;

Apartment::Apartment(City &city, int population) : Residential(city, population) {}

Building::Type Apartment::get_type() const
{
    return Building::Type::APARTMENT;
}

int Apartment::get_cost() const
{
    return this->cost;
}

std::string Apartment::get_long_information() const
{
    return APARTMENT_HEADER + '\n' + APARTMENT_1_1 + std::to_string(Building::get_population()) + '\n' + APARTMENT_2_1 + std::to_string(Building::get_max_population()) + '\n' + APARTMENT_3_1 + '\n' + APARTMENT_4_1 + std::to_string(Building::get_population_growth_rate_contribution()) + '\n' + APARTMENT_5_1 + '\n' + APARTMENT_6_1 + std::to_string(Building::get_population_growth()) + APARTMENT_6_2 + std::to_string(Building::get_max_population() - Building::get_population()) + APARTMENT_6_3 + '\n' + APARTMENT_7_1 + '\n';
}

std::string Apartment::get_short_information() const
{
    return APARTMENT_HEADER + '\n' + APARTMENT_1_1 + std::to_string(Building::get_population()) + '\n' + APARTMENT_2_1 + std::to_string(Building::get_max_population()) + '\n' + APARTMENT_4_1 + std::to_string(Building::get_population_growth_rate_contribution()) + '\n' + APARTMENT_6_1 + std::to_string(Building::get_population_growth()) + '\n';
}

int Apartment::get_revenue() const { return 0; }
int Apartment::get_max_population() const { return 250 * (1 + Building::number_neighboring_residential_buildings()); }
int Apartment::get_population_growth() const
{
    return city.get_population_growth_rate() * (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10 <
                   Building::get_max_population() - Building::get_population()
               ? city.get_population_growth_rate() *
                     (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10
               : Building::get_max_population() - Building::get_population();
}

#include "Hospital.h"
#include "../City.h"
using namespace std;

Hospital::Hospital(City &city) : Health(city) {}

Building::Type Hospital::get_type() const
{
    return Building::Type::HOSPITAL;
}

int Hospital::get_cost() const
{
    return this->cost;
}

std::string Hospital::get_long_information() const
{
    return HOSPITAL_HEADER + '\n' +
           HOSPITAL_1_1 + std::to_string(360 / (1 + Building::number_neighboring_health_buildings())) + '\n' +
           HOSPITAL_2_1 + '\n';
}

std::string Hospital::get_short_information() const
{
    return HOSPITAL_HEADER + '\n' +
           HOSPITAL_1_1 + std::to_string(360 / (1 + Building::number_neighboring_health_buildings())) + '\n';
}

int Hospital::get_revenue() const { return 0; }
int Hospital::get_population() const { return 0; }
int Hospital::get_max_population() const { return 0; }
int Hospital::get_population_growth() const { return 0; }
int Hospital::get_population_growth_rate_contribution() const { return 360 / (1 + Building::number_neighboring_health_buildings()); }
void Hospital::increase_population(int population) { population = 0; }
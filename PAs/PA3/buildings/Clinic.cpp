// #include "Clinic.h"
#include "../City.h"
using namespace std;

Clinic::Clinic(City &city) : Health(city) {}

Building::Type Clinic::get_type() const
{
    return Building::Type::CLINIC;
}

int Clinic::get_cost() const
{
    return this->cost;
}

std::string Clinic::get_long_information() const
{
    return CLINIC_HEADER + '\n' + CLINIC_1_1 + std::to_string(60 / (1 + Building::number_neighboring_health_buildings())) + '\n' +
           CLINIC_2_1 + '\n';
}

std::string Clinic::get_short_information() const
{
    return CLINIC_HEADER + '\n' +
           CLINIC_1_1 + std::to_string(60 / (1 + Building::number_neighboring_health_buildings())) + '\n';
}

int Clinic::get_revenue() const { return 0; }
int Clinic::get_population() const { return 0; }
int Clinic::get_max_population() const { return 0; }
int Clinic::get_population_growth() const { return 0; }
int Clinic::get_population_growth_rate_contribution() const { return 60 / (1 + Building::number_neighboring_health_buildings()); }
void Clinic::increase_population(int population) { population += 0; }
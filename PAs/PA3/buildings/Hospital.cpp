#include "buildings/Hospital.h"
#include "City.h"
using namespace std;

Hospital::Hospital(City &city) : Health(city) {}

Building::Type Hospital::get_type() const
{
    return this->type;
}

int Hospital::get_cost() const
{
    return this->cost;
}

std::string Hospital::get_long_information() const
{
    cout << HOSPITAL_HEADER << endl;
    cout << HOSPITAL_1_1 << 360 / (1 + Building::number_neighboring_health_buildings()) << endl;
    cout << HOSPITAL_2_1 << endl;
}

std::string Hospital::get_short_information() const
{
    cout << HOSPITAL_HEADER << endl;
    cout << HOSPITAL_1_1 << 360 / (1 + Building::number_neighboring_health_buildings()) << endl;
}

int Hospital::get_revenue() const { return 0; }
int Hospital::get_population() const { return 0; }
int Hospital::get_max_population() const { return 0; }
int Hospital::get_population_growth() const { return 0; }
int Hospital::get_population_growth_rate_contribution() const { return 360 / (1 + Building::number_neighboring_health_buildings()); }
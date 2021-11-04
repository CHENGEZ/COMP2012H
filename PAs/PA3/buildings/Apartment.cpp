#include "buildings/Apartment.h"
#include "City.h"
using namespace std;

Apartment::Apartment(City &city, int population) : Residential(city, population) {}

Building::Type Apartment::get_type() const
{
    return this->type;
}

int Apartment::get_cost() const
{
    return this->cost;
}

std::string Apartment::get_long_information() const
{
    cout << APARTMENT_HEADER << endl;
    cout << APARTMENT_1_1 << Building::get_population() << endl;
    cout << APARTMENT_2_1 << Building::get_max_population() << endl;
    cout << APARTMENT_3_1 << endl;
    cout << APARTMENT_4_1 << Building::get_population_growth_rate_contribution() << endl;
    cout << APARTMENT_5_1 << endl;
    cout << APARTMENT_6_1 << Building::get_population_growth() << APARTMENT_6_2
         << Building::get_max_population() - Building::get_population() << APARTMENT_6_3 << endl;
    cout << APARTMENT_7_1 << endl;
}

std::string Apartment::get_short_information() const
{
    cout << APARTMENT_HEADER << endl;
    cout << APARTMENT_1_1 << Building::get_population() << endl;
    cout << APARTMENT_2_1 << Building::get_max_population() << endl;
    cout << APARTMENT_4_1 << Building::get_population_growth_rate_contribution() << endl;
    cout << APARTMENT_6_1 << Building::get_population_growth() << endl;
}

int Apartment::get_revenue() const { return 0; }
int Apartment::get_population() const { return Residential::population; }
int Apartment::get_max_population() const { return 250 * (1 + Building::number_neighboring_residential_buildings()); }
int Apartment::get_population_growth() const
{
    return city.get_population_growth_rate() * (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10 <
                   Building::get_max_population() - Building::get_population()
               ? city.get_population_growth_rate() *
                     (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10
               : Building::get_max_population() - Building::get_population();
}

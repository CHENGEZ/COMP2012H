#include "House.h"
#include "../City.h"

using namespace std;

House::House(City &city, int population) : Residential(city, population) {}

Building::Type House::get_type() const
{
    return this->type;
}

int House::get_cost() const
{
    return this->cost;
}

std::string House::get_long_information() const
{
    cout << HOUSE_HEADER << endl;
    cout << HOUSE_1_1 << get_population() << endl;
    cout << HOUSE_2_1 << get_max_population() << endl;
    cout << HOUSE_3_1 << endl;
    cout << HOUSE_4_1 << get_population_growth_rate_contribution() << endl;
    cout << HOUSE_5_1 << endl;
    cout << HOUSE_6_1 << get_population_growth() << HOUSE_6_2
         << get_max_population() - get_population() << HOUSE_6_3 << endl;
    cout << HOUSE_7_1 << endl;
}

std::string House::get_short_information() const
{
    cout << HOUSE_HEADER << endl;
    cout << HOUSE_1_1 << Building::get_population() << endl;
    cout << HOUSE_2_1 << Building::get_max_population() << endl;
    cout << HOUSE_4_1 << Building::get_population_growth_rate_contribution() << endl;
    cout << HOUSE_6_1 << Building::get_population_growth() << endl;
}

int House::get_revenue() const { return 0; }
int House::get_population() const { return Residential::population; }
int House::get_max_population() const { return 50 * (1 + Building::number_neighboring_residential_buildings()); }
int House::get_population_growth() const
{
    return city.get_population_growth_rate() * (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10 <
                   Building::get_max_population() - Building::get_population()
               ? city.get_population_growth_rate() *
                     (Building::number_neighboring_health_buildings() - Building::number_neighboring_gold_mines()) / 10
               : Building::get_max_population() - Building::get_population();
}
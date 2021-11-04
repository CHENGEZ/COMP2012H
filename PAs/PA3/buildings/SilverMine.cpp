#include "SilverMine.h"
#include "../City.h"

using namespace std;

SilverMine::SilverMine(City &city) : Revenue(city) {}

Building::Type SilverMine::get_type() const
{
    return this->type;
}

int SilverMine::get_cost() const
{
    return this->cost;
}

std::string SilverMine::get_long_information() const
{
    cout << SILVER_HEADER << endl;
    cout << SILVER_1_1 << Building::number_neighboring_population() + city.get_population() << endl;
    cout << SILVER_2_1 << endl;
}

std::string SilverMine::get_short_information() const
{
    cout << SILVER_HEADER << endl;
    cout << SILVER_1_1 << Building::number_neighboring_population() + city.get_population() << endl;
}

int SilverMine::get_revenue() const
{
    return Building::number_neighboring_population() + city.get_population();
}

int SilverMine::get_population() const { return 0; }
int SilverMine::get_max_population() const { return 0; }
int SilverMine::get_population_growth() const { return 0; }
int SilverMine::get_population_growth_rate_contribution() const { return 0; }

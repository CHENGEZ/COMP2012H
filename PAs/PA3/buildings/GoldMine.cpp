#include "buildings/GoldMine.h"
#include "City.h"

using namespace std;

GoldMine::GoldMine(City &city) : Revenue(city) {}

Building::Type GoldMine::get_type() const
{
    return this->type;
}

int GoldMine::get_cost() const
{
    return this->cost;
}

std::string GoldMine::get_long_information() const
{
    cout << GOLD_HEADER << endl;
    cout << GOLD_1_1 << 2 * (Building::number_neighboring_population() + city.get_population()) << endl;
    cout << GOLD_2_1 << endl;
}

std::string GoldMine::get_short_information() const
{
    cout << GOLD_HEADER << endl;
    cout << GOLD_1_1 << 2 * (Building::number_neighboring_population() + city.get_population()) << endl;
}

int GoldMine::get_revenue() const
{
    return 2 * (Building::number_neighboring_population() + city.get_population());
}

int GoldMine::get_population() const { return 0; }
int GoldMine::get_max_population() const { return 0; }
int GoldMine::get_population_growth() const { return 0; }
int GoldMine::get_population_growth_rate_contribution() const { return 0; }

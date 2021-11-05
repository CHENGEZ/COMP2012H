#include "Building.h"
// #include "../City.h"

Building::Building(City &city) : city(city) {}

bool Building::register_neighboring_building(Building *building)
{
    // check if this "building" is already registered
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] == building)
        {
            return false;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] == nullptr)
        {
            neighboring_buildings[i] = building;
            return true;
        }
    }
}

bool Building::deregister_neighboring_building(Building *building)
{
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] == building)
        {
            neighboring_buildings[i] = nullptr;
            return true;
        }
    }

    return false;
}

int Building::number_neighboring_residential_buildings() const
{
    int number_neighboring_residential_buildings = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr)
        {
            if (neighboring_buildings[i]->get_category() == Category::RESIDENTIAL)
            {
                number_neighboring_residential_buildings++;
            }
        }
    }
    return number_neighboring_residential_buildings;
}

int Building::number_neighboring_health_buildings() const
{
    int number_neighboring_health_buildings = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr)
        {
            if (neighboring_buildings[i]->get_category() == Category::HEALTH)
            {
                number_neighboring_health_buildings++;
            }
        }
    }
    return number_neighboring_health_buildings;
}

int Building::number_neighboring_gold_mines() const
{
    int number_neighboring_gold_mines = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr)
        {
            if (neighboring_buildings[i]->get_type() == Building::Type::GOLD_MINE)
            {
                number_neighboring_gold_mines++;
            }
        }
    }
    return number_neighboring_gold_mines;
}

int Building::number_neighboring_population() const
{
    int sum_of_population = 0;
    for (int i = 0; i < 4; i++)
    {
        if (neighboring_buildings[i] != nullptr)
        {
            sum_of_population += neighboring_buildings[i]->get_population();
        }
    }

    return sum_of_population;
}

/*dummy implementation*/
int Building::get_revenue() const { return 0; }
int Building::get_population() const { return 0; }
int Building::get_max_population() const { return 67; }
int Building::get_population_growth() const { return 0; }
int Building::get_population_growth_rate_contribution() const { return 0; }
void Building::increase_population(int population) {}
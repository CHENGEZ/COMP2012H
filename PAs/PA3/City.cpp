#include "City.h"
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

City::City(int size)
{
    /* Allocate the 2D array of grid cells with dimensions size by size */
    this->grid = new Building **[size];
    for (int j = 0; j < size; j++)
    {
        grid[j] = new Building *[size];
    }

    /*Set all grid cells to nullptr*/
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            grid[x][y] = nullptr;
        }
    }

    this->grid_size = size; // Set grid size accordingly
    this->turn = 1;         // Set turn to 1
    this->budget = 150;     // Initially, the budget is $150
}

struct Data
{
    int buildingTypeNumber;
    int pop;
};

City::City(const std::string &filename)
{
    ifstream ifs;
    ifs.open(filename);
    char thisLine[11] = {};
    int numberLength = 0;

    /* grid_size*/
    ifs.getline(thisLine, 11);
    for (numberLength = 0; numberLength < 11; numberLength++)
    {
        if (thisLine[numberLength] == '\0')
        {
            break;
        }
    }
    for (int i = 0; i <= numberLength - 1; i++)
    {
        grid_size += ((int)thisLine[numberLength - (i + 1)] - 48) * pow(10, i);
    }

    /* budget */
    ifs.getline(thisLine, 11);
    for (numberLength = 0; numberLength < 11; numberLength++)
    {
        if (thisLine[numberLength] == '\0')
        {
            break;
        }
    }
    for (int i = 0; i <= numberLength - 1; i++)
    {
        budget += ((int)thisLine[numberLength - (i + 1)] - 48) * pow(10, i);
    }

    /* turns */
    ifs.getline(thisLine, 11);
    for (numberLength = 0; numberLength < 11; numberLength++)
    {
        if (thisLine[numberLength] == '\0')
        {
            break;
        }
    }
    for (int i = 0; i <= numberLength - 1; i++)
    {
        turn += ((int)thisLine[numberLength - (i + 1)] - 48) * pow(10, i);
    }

    /* The grid */
    Data tempMap[grid_size][grid_size] = {};
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            ifs.getline(thisLine, 11);
            if (thisLine[1] == '\0') // no buildng or not a residential building
            {
                tempMap[x][y].buildingTypeNumber = (int)thisLine[0] - 48;
                tempMap[x][y].pop = 0;
            }
            else // a residential building
            {
                tempMap[x][y].buildingTypeNumber = (int)thisLine[0] - 48;
                for (numberLength = 0; numberLength < 11; numberLength++)
                {
                    if (thisLine[numberLength + 2] == '\0')
                    {
                        break;
                    }
                }
                for (int i = 0; i <= numberLength - 1; i++)
                {
                    tempMap[x][y].pop += ((int)thisLine[numberLength - (i + 1) + 2] - 48) * pow(10, i);
                }
            }
        }
    }

    /* Allocate the 2D array of grid cells with dimensions size by size */
    this->grid = new Building **[grid_size];

    for (int j = 0; j < grid_size; j++)
    {
        grid[j] = new Building *[grid_size];
    }

    /* Load the grid */
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            switch (tempMap[x][y].buildingTypeNumber)
            {
            case 0:
                grid[x][y] = nullptr;
                break;

            case 1:
                grid[x][y] = new Clinic(*this);
                break;

            case 2:
                grid[x][y] = new Hospital(*this);
                break;

            case 3:
                grid[x][y] = new SilverMine(*this);
                break;

            case 4:
                grid[x][y] = new GoldMine(*this);
                break;

            case 5:
                grid[x][y] = new House(*this, tempMap[x][y].pop);
                break;

            case 6:
                grid[x][y] = new Apartment(*this, tempMap[x][y].pop);
                break;

            default:
                break;
            }
        }
    }

    /* register neighboring buildings*/
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
            {
                if (x - 1 >= 0 && grid[x - 1][y] != nullptr)
                {
                    grid[x - 1][y]->register_neighboring_building(grid[x][y]);
                }
                if (x + 1 <= grid_size - 1 && grid[x + 1][y] != nullptr)
                {
                    grid[x + 1][y]->register_neighboring_building(grid[x][y]);
                }
                if (y - 1 >= 0 && grid[x][y - 1] != nullptr)
                {
                    grid[x][y - 1]->register_neighboring_building(grid[x][y]);
                }
                if (y + 1 <= grid_size - 1 && grid[x][y + 1] != nullptr)
                {
                    grid[x][y + 1]->register_neighboring_building(grid[x][y]);
                }
            }
        }
    }

    ifs.close();
}

City::~City()
{
    // go through the whole square grid to deallocate the memory of the building objects
    for (int x = 0; x < this->grid_size; x++)
    {
        for (int y = 0; y < this->grid_size; y++)
        {
            delete this->grid[x][y];
            this->grid[x][y] = nullptr;
        }
    }

    // deallocate the memory of the map
    for (int i = 0; i < this->grid_size; i++)
    {
        delete[] this->grid[i];
        this->grid[i] = nullptr;
    }

    // deallocate the 1D array storing pointers to rows of the map
    delete[] this->grid;
    this->grid = nullptr;
}

void City::save(const std::string &filename) const
{
    /**/
}

int City::get_turn() const
{
    return this->turn;
}
int City::get_budget() const
{
    return this->budget;
}
int City::get_grid_size() const
{
    return this->grid_size;
}

int City::get_revenue() const
{
    int totalRevenue = 0;
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
                totalRevenue += grid[x][y]->get_revenue();
        }
    }

    return totalRevenue;
}

int City::get_population() const
{
    int totalPopulation = 0;
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
                totalPopulation += grid[x][y]->get_population();
        }
    }
    return totalPopulation;
}

int City::get_max_population() const
{
    int maxPopulation = 0;
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
                maxPopulation += grid[x][y]->get_max_population();
        }
    }
    return maxPopulation;
}

int City::get_population_growth() const
{
    int sum_of_population_growth = 0;
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
                sum_of_population_growth += grid[x][y]->get_population_growth();
        }
    }
    return sum_of_population_growth;
}

int City::get_population_growth_rate() const
{
    int sum_of_contribution = 0;
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
                sum_of_contribution += grid[x][y]->get_population_growth_rate_contribution();
        }
    }
    return sum_of_contribution;
}

Building *City::get_at(const Coordinates &coordinates) const
{
    if (coordinates.x > grid_size - 1 || coordinates.x < 0 || coordinates.y > grid_size - 1 || coordinates.y < 0)
    {
        return nullptr;
    }

    return grid[coordinates.x][coordinates.y];
}

bool City::is_empty_at(const Coordinates &coordinates) const
{
    if (coordinates.x > grid_size - 1 || coordinates.x < 0 || coordinates.y > grid_size - 1 || coordinates.y < 0)
        return false;

    if (grid[coordinates.x][coordinates.y] == nullptr)
        return true;
    else
        return false;
}

bool City::can_construct(Building::Type type) const
{
    int costOfThisType = 0;
    switch (type)
    {
    case Building::Type::APARTMENT:
        costOfThisType = 300;
        break;

    case Building::Type::HOUSE:
        costOfThisType = 50;
        break;

    case Building::Type::CLINIC:
        costOfThisType = 50;
        break;

    case Building::Type::HOSPITAL:
        costOfThisType = 500;
        break;

    case Building::Type::GOLD_MINE:
        costOfThisType = 400;
        break;

    case Building::Type::SILVER_MINE:
        costOfThisType = 50;
        break;

    default:
        break;
    }

    return budget >= costOfThisType ? true : false;
}

bool City::can_construct(Building::Type type, const Coordinates &coordinates) const
{
    bool enoughMoney = false, freeSpace = false;

    int costOfThisType = 0;
    switch (type)
    {
    case Building::Type::APARTMENT:
        costOfThisType = 300;
        break;

    case Building::Type::HOUSE:
        costOfThisType = 50;
        break;

    case Building::Type::CLINIC:
        costOfThisType = 50;
        break;

    case Building::Type::HOSPITAL:
        costOfThisType = 500;
        break;

    case Building::Type::GOLD_MINE:
        costOfThisType = 400;
        break;

    case Building::Type::SILVER_MINE:
        costOfThisType = 50;
        break;

    default:
        break;
    }

    enoughMoney = budget >= costOfThisType ? true : false;
    if (coordinates.x >= 0 && coordinates.x < grid_size && coordinates.y >= 0 && coordinates.y < grid_size) // in bound
    {
        if (grid[coordinates.x][coordinates.y] == nullptr) // no building existing
        {
            freeSpace = true;
        }
    }

    if (enoughMoney && freeSpace)
        return turn;
    else
        return false;
}

bool City::construct_at(Building::Type type, const Coordinates &coordinates)
{
    if (!can_construct(type, coordinates))
        return false;

    switch (type)
    {
    case Building::Type::APARTMENT:
        grid[coordinates.x][coordinates.y] = new Apartment(*this, 0);
        this->budget -= 300;
        break;

    case Building::Type::HOUSE:
        grid[coordinates.x][coordinates.y] = new House(*this, 0);
        this->budget -= 50;
        break;

    case Building::Type::CLINIC:
        grid[coordinates.x][coordinates.y] = new Clinic(*this);
        this->budget -= 50;
        break;

    case Building::Type::HOSPITAL:
        grid[coordinates.x][coordinates.y] = new Hospital(*this);
        this->budget -= 500;
        break;

    case Building::Type::GOLD_MINE:
        grid[coordinates.x][coordinates.y] = new GoldMine(*this);
        this->budget -= 400;
        break;

    case Building::Type::SILVER_MINE:
        grid[coordinates.x][coordinates.y] = new SilverMine(*this);
        this->budget -= 50;
        break;

    default:
        break;
    }

    if (coordinates.x - 1 >= 0 && grid[coordinates.x - 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x - 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x - 1][coordinates.y]);
    }
    if (coordinates.x + 1 <= grid_size - 1 && grid[coordinates.x + 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x + 1][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x + 1][coordinates.y]);
    }
    if (coordinates.y - 1 >= 0 && grid[coordinates.x][coordinates.y - 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y - 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y - 1]);
    }
    if (coordinates.y + 1 <= grid_size - 1 && grid[coordinates.x][coordinates.y + 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y + 1]->register_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->register_neighboring_building(grid[coordinates.x][coordinates.y + 1]);
    }

    return true;
}

bool City::demolish_at(const Coordinates &coordinates)
{
    bool inBound = coordinates.x >= 0 && coordinates.x < grid_size && coordinates.y >= 0 && coordinates.y < grid_size;
    if (!inBound)
        return false;
    if (grid[coordinates.x][coordinates.y] == nullptr)
        return false;

    grid[coordinates.x][coordinates.y]->~Building();

    if (coordinates.x - 1 >= 0 && grid[coordinates.x - 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x - 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->deregister_neighboring_building(grid[coordinates.x - 1][coordinates.y]);
    }
    if (coordinates.x + 1 <= grid_size - 1 && grid[coordinates.x + 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x + 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->deregister_neighboring_building(grid[coordinates.x + 1][coordinates.y]);
    }
    if (coordinates.y - 1 >= 0 && grid[coordinates.x][coordinates.y - 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y - 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y - 1]);
    }
    if (coordinates.y + 1 <= grid_size - 1 && grid[coordinates.x][coordinates.y + 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y + 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
        grid[coordinates.x][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y + 1]);
    }

    grid[coordinates.x][coordinates.y] = nullptr;
    return true;
}

void City::move_to_next_turn()
{
    /*1.The turn number of the city is increased by one.*/
    this->turn += 1;

    /*2.the budget of the city is increased by the sum of revenue generated by all Revenue buildings.*/
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
            {
                this->budget += grid[x][y]->get_revenue();
            }
        }
    }

    /*3. the population is increased/decreased according to the game mechanics*/
    int pop_growth_for_this_residential_building = 0;
    int pop_growth_for_each_grid[grid_size][grid_size] = {};
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
            {
                pop_growth_for_this_residential_building = grid[x][y]->get_population_growth();
                pop_growth_for_each_grid[x][y] = pop_growth_for_this_residential_building;
            }
        }
    }
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] != nullptr)
            {
                grid[x][y]->increase_population(pop_growth_for_each_grid[x][y]);
            }
        }
    }
}
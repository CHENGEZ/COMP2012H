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

    grid_size = 0;
    budget = 0;
    turn = 0;
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
    Data **tempMap = new Data *[grid_size];
    for (int j = 0; j < grid_size; j++)
    {
        tempMap[j] = new Data[grid_size];
    }

    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            tempMap[x][y].buildingTypeNumber = 0;
            tempMap[x][y].pop = 0;
        }
    }

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

    for (int i = 0; i < grid_size; i++)
    {
        delete[] tempMap[i];
        tempMap[i] = nullptr;
    }

    delete[] tempMap;
    tempMap = nullptr;
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

int determineNumberLength(int number)
{
    if (number / 1000000000 >= 1)
        return 10;
    if (number / 100000000 >= 1)
        return 9;
    if (number / 10000000 >= 1)
        return 8;
    if (number / 1000000 >= 1)
        return 7;
    if (number / 100000 >= 1)
        return 6;
    if (number / 10000 >= 1)
        return 5;
    if (number / 1000 >= 1)
        return 4;
    if (number / 100 >= 1)
        return 3;
    if (number / 10 >= 1)
        return 2;

    return 1;
}

void clearArray(char array[10])
{
    for (int i = 0; i < 10; i++)
    {
        array[i] = 0;
    }
}

int convertNum2CharArray(int number, char array[10])
{
    clearArray(array);
    int numberLength = determineNumberLength(number);
    int firstDigit = 0, secondDigit = 0, thirdDigit = 0, forthDigit = 0, fifthDigit = 0, sixthDigit = 0, seventhDigit = 0, eighthDigit = 0, ninethDigit = 0, tenthDigit = 0;

    switch (numberLength)
    {
    case 1:
        firstDigit = number / 1;
        break;
    case 2:
        firstDigit = number / 10;
        secondDigit = number / 1 - (number / 10) * 10;
        break;
    case 3:
        firstDigit = number / 100;
        secondDigit = number / 10 - (number / 100) * 10;
        thirdDigit = number / 1 - (number / 10) * 10;
        break;
    case 4:
        firstDigit = number / 1000;
        secondDigit = number / 100 - (number / 1000) * 10;
        thirdDigit = number / 10 - (number / 100) * 10;
        forthDigit = number / 1 - (number / 10) * 10;
        break;
    case 5:
        firstDigit = number / 10000;
        secondDigit = number / 1000 - (number / 10000) * 10;
        thirdDigit = number / 100 - (number / 1000) * 10;
        forthDigit = number / 10 - (number / 100) * 10;
        fifthDigit = number / 1 - (number / 10) * 10;
        break;
    case 6:
        firstDigit = number / 100000;
        secondDigit = number / 10000 - (number / 100000) * 10;
        thirdDigit = number / 1000 - (number / 10000) * 10;
        forthDigit = number / 100 - (number / 1000) * 10;
        fifthDigit = number / 10 - (number / 100) * 10;
        sixthDigit = number / 1 - (number / 10) * 10;
        break;
    case 7:
        firstDigit = number / 1000000;
        secondDigit = number / 100000 - (number / 1000000) * 10;
        thirdDigit = number / 10000 - (number / 100000) * 10;
        forthDigit = number / 1000 - (number / 10000) * 10;
        fifthDigit = number / 100 - (number / 1000) * 10;
        sixthDigit = number / 10 - (number / 100) * 10;
        seventhDigit = number / 1 - (number / 10) * 10;
        break;
    case 8:
        firstDigit = number / 10000000;
        secondDigit = number / 1000000 - (number / 10000000) * 10;
        thirdDigit = number / 100000 - (number / 1000000) * 10;
        forthDigit = number / 10000 - (number / 100000) * 10;
        fifthDigit = number / 1000 - (number / 10000) * 10;
        sixthDigit = number / 100 - (number / 1000) * 10;
        seventhDigit = number / 10 - (number / 100) * 10;
        eighthDigit = number / 1 - (number / 10) * 10;
        break;
    case 9:
        firstDigit = number / 100000000;
        secondDigit = number / 10000000 - (number / 100000000) * 10;
        thirdDigit = number / 1000000 - (number / 10000000) * 10;
        forthDigit = number / 100000 - (number / 1000000) * 10;
        fifthDigit = number / 10000 - (number / 100000) * 10;
        sixthDigit = number / 1000 - (number / 10000) * 10;
        seventhDigit = number / 100 - (number / 1000) * 10;
        eighthDigit = number / 10 - (number / 100) * 10;
        ninethDigit = number / 1 - (number / 10) * 10;
        break;
    case 10:
        firstDigit = number / 1000000000;
        secondDigit = number / 100000000 - (number / 1000000000) * 10;
        thirdDigit = number / 10000000 - (number / 100000000) * 10;
        forthDigit = number / 1000000 - (number / 10000000) * 10;
        fifthDigit = number / 100000 - (number / 1000000) * 10;
        sixthDigit = number / 10000 - (number / 100000) * 10;
        seventhDigit = number / 1000 - (number / 10000) * 10;
        eighthDigit = number / 100 - (number / 1000) * 10;
        ninethDigit = number / 10 - (number / 100) * 10;
        tenthDigit = number / 1 - (number / 10) * 10;
        break;

    default:
        break;
    }

    array[0] = (char)firstDigit + 48;
    array[1] = (char)secondDigit + 48;
    array[2] = (char)thirdDigit + 48;
    array[3] = (char)forthDigit + 48;
    array[4] = (char)fifthDigit + 48;
    array[5] = (char)sixthDigit + 48;
    array[6] = (char)seventhDigit + 48;
    array[7] = (char)eighthDigit + 48;
    array[8] = (char)ninethDigit + 48;
    array[9] = (char)tenthDigit + 48;

    return numberLength;
}

void City::save(const std::string &filename) const
{
    ofstream ofs;
    ofs.open(filename);

    int thisNumberLength = 0;
    Building::Type thisBuildingType;

    char numberArray[10] = {};

    /* grid_size */
    thisNumberLength = convertNum2CharArray(grid_size, numberArray);
    for (int i = 0; i < thisNumberLength; i++)
    {
        ofs.put(numberArray[i]);
    }
    ofs.put('\n');

    /* budget */
    thisNumberLength = convertNum2CharArray(budget, numberArray);
    for (int i = 0; i < thisNumberLength; i++)
    {
        ofs.put(numberArray[i]);
    }
    ofs.put('\n');

    /*turn*/
    thisNumberLength = convertNum2CharArray(turn, numberArray);
    for (int i = 0; i < thisNumberLength; i++)
    {
        ofs.put(numberArray[i]);
    }
    ofs.put('\n');

    /* grid */
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            if (grid[x][y] == nullptr)
            {
                ofs.put('0');
                ofs.put('\n');
            }
            if (grid[x][y] != nullptr)
            {
                if (grid[x][y]->get_category() == Building::Category::RESIDENTIAL) // residential building: store both building type and population
                {
                    thisBuildingType = grid[x][y]->get_type();
                    switch (thisBuildingType)
                    {
                    case Building::Type::APARTMENT:
                        ofs.put('6');
                        ofs.put(' ');
                        break;
                    case Building::Type::HOUSE:
                        ofs.put('5');
                        ofs.put(' ');
                        break;
                    default:
                        break;
                    }

                    thisNumberLength = convertNum2CharArray(grid[x][y]->get_population(), numberArray);
                    for (int i = 0; i < thisNumberLength; i++)
                    {
                        ofs.put(numberArray[i]);
                    }
                    ofs.put('\n');
                }
                else // not residential building, just store building type
                {
                    thisBuildingType = grid[x][y]->get_type();
                    switch (thisBuildingType)
                    {
                    case Building::Type::CLINIC:
                        ofs.put('1');
                        ofs.put('\n');
                        break;
                    case Building::Type::GOLD_MINE:
                        ofs.put('4');
                        ofs.put('\n');
                        break;
                    case Building::Type::HOSPITAL:
                        ofs.put('2');
                        ofs.put('\n');
                        break;
                    case Building::Type::SILVER_MINE:
                        ofs.put('3');
                        ofs.put('\n');
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    ofs.close();
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

    if (coordinates.x - 1 >= 0 && grid[coordinates.x - 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x - 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    }
    if (coordinates.x + 1 <= grid_size - 1 && grid[coordinates.x + 1][coordinates.y] != nullptr)
    {
        grid[coordinates.x + 1][coordinates.y]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    }
    if (coordinates.y - 1 >= 0 && grid[coordinates.x][coordinates.y - 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y - 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    }
    if (coordinates.y + 1 <= grid_size - 1 && grid[coordinates.x][coordinates.y + 1] != nullptr)
    {
        grid[coordinates.x][coordinates.y + 1]->deregister_neighboring_building(grid[coordinates.x][coordinates.y]);
    }

    delete grid[coordinates.x][coordinates.y];
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
    //int pop_growth_for_each_grid[grid_size][grid_size] = {};
    int **pop_growth_for_each_grid = new int *[grid_size];
    for (int i = 0; i < grid_size; i++)
    {
        pop_growth_for_each_grid[i] = new int[grid_size];
    }

    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            pop_growth_for_each_grid[x][y] = 0;
        }
    }

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

    for (int i = 0; i < grid_size; i++)
    {
        delete[] pop_growth_for_each_grid[i];
        pop_growth_for_each_grid[i] = nullptr;
    }
    delete[] pop_growth_for_each_grid;
    pop_growth_for_each_grid = nullptr;
}
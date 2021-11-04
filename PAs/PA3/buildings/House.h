#ifndef HOUSE_H
#define HOUSE_H

#include "Residential.h"
class House : public Residential
{
private:
    Building::Type type = Building::Type::HOUSE;
    static const int cost{50};

public:
    House(City &city, int population);
    Building::Type get_type() const;
    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;
    int get_revenue() const;
    int get_population() const;
    int get_max_population() const;
    int get_population_growth() const;
};
#endif // HOUSE_H

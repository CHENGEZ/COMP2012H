#ifndef APARTMENT_H
#define APARTMENT_H

#include "Residential.h"
class Apartment : public Residential
{
private:
    Building::Type type = Building::Type::APARTMENT;
    static const int cost{300};

public:
    Apartment(City &city, int population);
    Building::Type get_type() const;
    int get_cost() const;

    std::string get_long_information() const;
    std::string get_short_information() const;
    int get_revenue() const;
    int get_population() const;
    int get_max_population() const;
    int get_population_growth() const;
};
#endif // APARTMENT_H

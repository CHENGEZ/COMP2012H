#ifndef APARTMENT_H
#define APARTMENT_H

#include "Residential.h"
class Apartment : public Residential
{
private:
    static const int cost{300};

public:
    Apartment(City &city, int population);

    Building::Type get_type() const override;
    int get_cost() const override;
    std::string get_long_information() const override;
    std::string get_short_information() const override;

    int get_revenue() const override;
    int get_max_population() const override;
    int get_population_growth() const override;
};
#endif // APARTMENT_H

#ifndef HOUSE_H
#define HOUSE_H

#include "Residential.h"
class House : public Residential
{
private:
    static const int cost{50};

public:
    House(City &city, int population);

    Building::Type get_type() const override;
    int get_cost() const override;
    std::string get_long_information() const override;
    std::string get_short_information() const override;

    int get_revenue() const override;
    int get_max_population() const override;
    int get_population_growth() const override;
};
#endif // HOUSE_H

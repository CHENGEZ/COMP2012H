#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "Revenue.h"
class GoldMine : public Revenue
{
private:
    static const int cost{400};

public:
    GoldMine(City &city);

    Building::Type get_type() const;
    int get_cost() const;
    std::string get_long_information() const;
    std::string get_short_information() const;

    int get_revenue() const;
    int get_population() const;
    int get_max_population() const;
    int get_population_growth() const;
    int get_population_growth_rate_contribution() const;
    void increase_population(int population);
};
#endif // GOLDMINE_H

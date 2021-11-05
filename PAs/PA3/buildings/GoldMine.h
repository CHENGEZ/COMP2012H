#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "Revenue.h"
class GoldMine : public Revenue
{
private:
    static const int cost{400};

public:
    GoldMine(City &city);

    Building::Type get_type() const override;
    int get_cost() const override;
    std::string get_long_information() const override;
    std::string get_short_information() const override;

    int get_revenue() const override;
    int get_population() const override;
    int get_max_population() const override;
    int get_population_growth() const override;
    int get_population_growth_rate_contribution() const override;
    void increase_population(int population) override;
};
#endif // GOLDMINE_H

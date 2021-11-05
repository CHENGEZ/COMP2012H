#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Health.h"
class Hospital : public Health
{
private:
    static const int cost{500};

public:
    Hospital(City &city);

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
#endif // HOSPITAL_H

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Health.h"
class Hospital : public Health
{
private:
    static const int cost{500};

public:
    Hospital(City &city);

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
#endif // HOSPITAL_H

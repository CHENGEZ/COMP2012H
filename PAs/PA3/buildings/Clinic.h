#ifndef CLINIC_H
#define CLINIC_H

#include "Health.h"
class Clinic : public Health
{
private:
    static const int cost{50};

public:
    Clinic(City &city);

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
#endif // CLINIC_H

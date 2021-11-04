#ifndef HEALTH_H
#define HEALTH_H

#include "Building.h"
#include <iostream>
#include "BuildingInformationFormatString.h"
class Health : public Building
{
private:
    Building::Category category = Building::Category::HEALTH;

protected:
    Health(City &city);

public:
    virtual Building::Type get_type() const = 0;
    virtual int get_cost() const = 0;
    Building::Category get_category() const;

    virtual std::string get_long_information() const = 0;
    virtual std::string get_short_information() const = 0;
    virtual int get_revenue() const;
    virtual int get_population() const;
    virtual int get_max_population() const;
    virtual int get_population_growth() const;
    virtual int get_population_growth_rate_contribution() const;
    virtual void increase_population(int population);
};
#endif // HEALTH_H

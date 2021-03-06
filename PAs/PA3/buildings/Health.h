#ifndef HEALTH_H
#define HEALTH_H

#include "Building.h"
#include <iostream>
#include "BuildingInformationFormatString.h"
class Health : public Building
{
protected:
    Health(City &city);

public:
    /*no implementation needed*/
    virtual Building::Type get_type() const = 0;
    virtual int get_cost() const = 0;
    virtual std::string get_long_information() const = 0;
    virtual std::string get_short_information() const = 0;

    /*implementation is needed*/
    Building::Category get_category() const;

    /*dummy implementation will be needed*/
    virtual int get_revenue() const override;
    virtual int get_population() const override;
    virtual int get_max_population() const override;
    virtual int get_population_growth() const override;
    virtual int get_population_growth_rate_contribution() const override;
    virtual void increase_population(int population) override;
};
#endif // HEALTH_H

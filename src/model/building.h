#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <set>

#include "model/unit.h"

namespace aoe
{

class Technology;
class UnitDescription;

class Building : public Unit
{
private:
public:
    Building(UnitDescription* desc);
    ~Building();

    void create_unit(const std::string& name);
    void research_technology(const std::string& name);

};

}

#endif // BUILDING_H

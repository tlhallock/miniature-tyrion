#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <vector>

#include "model/unit.h"

class Technology;
class UnitDescription;

class Building : public Unit
{
private:
    Player *parent;

    std::vector<UnitDescription*> units;
    std::vector<Technology> techs;

public:
    Building(UnitDescription* desc);
    ~Building();

    void create_unit(const std::string& name);
    void research_technology(const std::string& name);

};

#endif // BUILDING_H

#ifndef CIVILIZATION_H
#define CIVILIZATION_H

#include <iostream>
#include <map>
#include <set>

#include "res/technology.h"
#include "res/unit_descp.h"

namespace aoe
{

class Location;

class Civilization
{
private:
    std::string name;
    std::set<int> buildings;
    std::vector<UnitDescription> unit_values;

public:
    Civilization(const std::string& name, const std::vector<UnitDescription>& units);
    ~Civilization();

    void enable(int building);
    void disable(int building);
    const std::set<int>& get_available_buildings() const;
    bool is_enabled(int building) const;

    Unit* create_building(int building_id, const Location& area, bool override=false) const;
};

}

#endif // CIVILIZATION_H

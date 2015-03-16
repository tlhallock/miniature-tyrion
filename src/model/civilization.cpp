#include "civilization.h"

#include "res/game_info.h"
#include "model/player.h"
#include "model/unit.h"

namespace aoe
{

Civilization::Civilization(const std::string& name_, const std::vector<UnitDescription>& units_) :
    name{name_},
    unit_values{units_} {}

Civilization::~Civilization() {}


void Civilization::enable(int building)
{
    buildings.insert(building);
}

void Civilization::disable(int building)
{
    buildings.erase(building);
}

const std::set<int>& Civilization::get_available_buildings() const
{
    return buildings;
}

bool Civilization::is_enabled(int building) const
{
    return buildings.find(building) != buildings.end();
}


Unit* Civilization::create_building(int building_id, const Location& area) const
{
    if (!is_enabled(building_id))
    {
        return nullptr;
    }

    Unit* unit = unit_values[building_id].create();

    unit->getArea() = area;

    return unit;
}


#if 0
const std::set<int>& Civilization::get_available_units(int building) const
{
    auto it = units.find(building);
    if (it == units.end())
    {
        units.insert(std::pair<int, std::set<int>>{building, std::set<int>{}});
        it = units.find(building);
    }
    return it->second;
}

void Civilization::enable(int building, int unit)
{
    auto it = units.find(building);
    if (it == units.end())
    {
        units.insert(std::pair<int, std::set<int>>{building, std::set<int>{}});
        it = units.find(building);
    }

    it->second.insert(unit);
}

#endif

}

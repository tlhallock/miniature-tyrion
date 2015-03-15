#include "map.h"
#include <cmath>

#include "main/settings.h"
#include "gfx/viewport_listener.h"

# define PI           3.14159265358979323846



namespace aoe
{

Map::Map() :
    width{Settings::get_instance().MAP_WIDTH},
    height{Settings::get_instance().MAP_HEIGHT} {}
Map::~Map() {}

void Map::place_unit(Unit* unit)
{
    units.push_back(std::unique_ptr<Unit>{unit});
}

void Map::place_resource(Resource* res)
{
    resources.push_back(std::unique_ptr<Resource>{res});
}

void Map::remove_unit(Unit* unit)
{
       // delete them somewhere
}

void Map::remove_resource(Resource* res)
{
    // delete them somewhere
}

Location Map::get_civilization_center(int index, int total)
{
    double cx = width / 2;
    double cy = height / 2;

    double angle = 2 * PI * index / total;

    double percent_of_radius = Settings::get_instance().PERCENT_OF_RADIUS;

    return Location{cx + percent_of_radius * cx * cos(angle),
                cy + percent_of_radius * cy * sin(angle)};
}


void Map::add_listener(ViewportListener* res)
{
    for (auto it = units.begin(); it != units.end(); ++it)
    {
        res->unit_entered(it->get());
    }
    listeners.insert(res);
}

void Map::remove_listener(ViewportListener* units)
{
    auto it = listeners.find(units);
    if (it == listeners.end())
    {
        return;
    }
    listeners.erase(it);
}

const std::vector<std::unique_ptr<Unit>>& Map::get_units() const { return units; }
const std::vector<std::unique_ptr<Resource>>& Map::get_resources() const { return resources; }



std::ostream& operator<<(std::ostream& out, const Map& g)
{
    out << "Size: " << g.width << "," << g.height << '\n';

    out << "Units:\n";
    for (int i=0;i<g.units.size();i++)
    {
        out << '\t' << i << ": " << *g.units[i] << '\n';
    }

    out << "Resources:\n";
    for (int i=0;i<g.resources.size();i++)
    {
        out << '\t' << i << ": " << *g.resources[i] << '\n';
    }
    return out;
}



bool Map::is_obstructed(const Area& area) const
{
    if (area.x < 0 || area.x + area.w > width || area.y < 0 || area.y + area.h > height)
    {
        return true;
    }

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        if ((*it)->get_location().overlaps(area))
        {
            return true;
        }
    }
    for (auto it = resources.begin(); it != resources.end(); ++it)
    {
        if ((*it)->get_location().overlaps(area))
        {
            return true;
        }
    }
    return false;
}


}

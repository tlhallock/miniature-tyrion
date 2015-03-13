#include "map.h"
#include <cmath>

#include "main/settings.h"

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

const Area&& Map::get_civilization_center(int index, int total)
{
    double cx = width / 2;
    double cy = height / 2;

    double angle = 2 * PI * index / total;

    double percent_of_radius = Settings::get_instance().PERCENT_OF_RADIUS;

    return Area{cx + percent_of_radius * cx * cos(angle),
                cy + percent_of_radius * cy * sin(angle), 0, 0};
}

const std::vector<std::unique_ptr<Unit>>& Map::get_units() const { return units; }
const std::vector<std::unique_ptr<Resource>>& Map::get_resources() const { return resources; }



std::ostream& operator<<(std::ostream& out, const Map& g)
{
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



}

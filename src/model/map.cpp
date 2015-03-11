#include "map.h"

namespace aoe
{

Map::Map() {}
Map::~Map() {}

void Map::place_unit(Unit* unit)
{
    units.push_back(std::unique_ptr<Unit>{unit});
}

void Map::place_resource(Resource* res)
{
    resources.push_back(std::unique_ptr<Resource>{res});
}

const std::vector<std::unique_ptr<Unit>>& Map::get_units() const { return units; }
const std::vector<std::unique_ptr<Resource>>& Map::get_resources() const { return resources; }




}

#include "map.h"

#define WIDTH 1000
#define HEIGHT 1000

namespace aoe
{

Map::Map() :
    width{WIDTH},
    height{HEIGHT} {}
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

const std::vector<std::unique_ptr<Unit>>& Map::get_units() const { return units; }
const std::vector<std::unique_ptr<Resource>>& Map::get_resources() const { return resources; }




}

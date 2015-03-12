#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>

#include "model/unit.h"
#include "model/resource.h"

namespace aoe
{

class Building;
class Area;

class Map
{
private:
    std::vector<std::unique_ptr<Unit>> units;
    std::vector<std::unique_ptr<Resource>> resources;
    double width, height;

public:
    Map();
    ~Map();

    void place_unit(Unit* units);
    void place_resource(Resource* res);

    void remove_unit(Unit* units);
    void remove_resource(Resource* units);

    const std::vector<std::unique_ptr<Unit>>& get_units() const;
    const std::vector<std::unique_ptr<Resource>>& get_resources() const;

    const Area&& get_civilization_center(int index, int total);
};

}

#endif // MAP_H

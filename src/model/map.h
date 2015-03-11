#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>

#include "model/unit.h"
#include "model/resource.h"

class Building;
class Area;

class Map
{
private:
    std::vector<std::unique_ptr<Unit>> units;
    std::vector<std::unique_ptr<Resource>> resources;

public:
    Map();
    ~Map();

    void place_unit(Unit* building);
    void place_resource(Resource* res);

    const std::vector<std::unique_ptr<Unit>>& get_units() const;
    const std::vector<std::unique_ptr<Resource>>& get_resources() const;
};

#endif // MAP_H

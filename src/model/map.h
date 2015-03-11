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
    std::vector<std::unique_ptr<Unit>> unit;
    std::vector<std::unique_ptr<Resource>> resources;

public:
    Map();
    ~Map();

    void place_unit(Building* building, const Area& area);
    void place_building(Building* building, const Area& area);
};

#endif // MAP_H

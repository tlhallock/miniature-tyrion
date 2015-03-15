#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>

#include "model/unit.h"
#include "model/resource.h"

#include <set>

namespace aoe
{

class ViewportListener;
class Building;
class Area;

class Map
{
private:
    std::vector<std::unique_ptr<Unit>> units;
    std::vector<std::unique_ptr<Resource>> resources;
    double width, height;

    std::set<ViewportListener*> listeners;
public:
    Map();
    ~Map();

    void place_unit(Unit* units);
    void remove_unit(Unit* units);

    void place_resource(Resource* res);
    void remove_resource(Resource* units);

    void add_listener(ViewportListener* res);
    void remove_listener(ViewportListener* units);

    bool is_obstructed(const Area& area) const;

    const std::vector<std::unique_ptr<Unit>>& get_units() const;
    const std::vector<std::unique_ptr<Resource>>& get_resources() const;

    Location get_civilization_center(int index, int total);

    friend std::ostream& operator<<(std::ostream& out, const Map& g);
};

}

#endif // MAP_H

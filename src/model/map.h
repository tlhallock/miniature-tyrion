#ifndef MAP_H
#define MAP_H

#include <vector>
#include <memory>

#include "model/unit.h"
#include "model/resource.h"
#include "model/spc/grid.h"

#include <set>

namespace aoe
{

class ViewportListener;
class Building;
class Area;

class Map
{
private:
    Grid spatials;

    double width, height;

    std::set<ViewportListener*> listeners;
public:
    Map();
    ~Map();

    void add(Spatial* unit);
    void remove(Spatial* unit);

    bool isInBounds(const Area& area) const;
    bool isObstructed(const Area& area);

    Location get_civilization_center(int index, int total);

    friend std::ostream& operator<<(std::ostream& out, const Map& g);

    void generateRangeNotifications(const std::set<Unit*>& moving_units);

    Location findNextDepositArea(Location center, Size toDeposit);
    Location findNextDepositArea(Location center, Size toDeposit, int &d, int &sq);
};

}

#endif // MAP_H

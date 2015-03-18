#include "map.h"
#include <cmath>

#include "main/settings.h"
#include "gfx/viewport_listener.h"

#include "model/spc/grid_internals.h"
#include "model/spc/area_spatial.h"


# define PI           3.14159265358979323846



namespace aoe
{


namespace
{
class GenerateInRangeEvent : public SpatialQuery
{
public:
    GenerateInRangeEvent(Unit* c) : SpatialQuery{c->getArea(), c->getType()->getRange()} {}
    ~GenerateInRangeEvent() {}

    virtual void apply(Spatial* sp)
    {
        // if is unit
        // if is enemy
        Unit* u = nullptr;

        u->broadcastEvent(UnitEvent::enemyInRange, nullptr);
    }
};


}

























Map::Map() :
    width{Settings::get_instance().MAP_WIDTH},
    height{Settings::get_instance().MAP_HEIGHT} {}
Map::~Map() {}


void Map::add(Spatial* unit)
{
    spatials.add(unit);
}

void Map::remove(Spatial* unit)
{
    spatials.add(unit);
    // delete it...
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


std::ostream& operator<<(std::ostream& out, const Map& g)
{
    out << "Size: " << g.width << "," << g.height << '\n';


    out << "Spatials:\n";
    out << g.spatials << std::endl;
}


bool Map::isInBounds(const Area& area) const
{
    return area.x >= 0 && area.x + area.width <= width && area.y >= 0 && area.y + area.height <= height;
}

bool Map::isObstructed(const Area& area)
{
    if (!isInBounds(area))
    {
        return true;
    }

    SimpleSpatial tmp{area};
    return spatials.overlaps(&tmp);
}

void Map::generateRangeNotifications(const std::set<Unit*>& moving_units)
{
    auto end = moving_units.end();
    for (auto it = moving_units.begin(); it != end; ++it)
    {
        Unit* u = *it;
        GenerateInRangeEvent eg{u};
        spatials.apply(&eg);
    }
}






}

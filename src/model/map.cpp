#include "map.h"
#include <cmath>

#include "main/settings.h"
#include "gfx/viewport_listener.h"

#include "model/spc/grid_internals.h"
#include "model/spc/area_spatial.h"
#include "model/engine.h"


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

    // where to delete it?
    // def. not here...
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

void Map::generateRangeNotifications(IterationInfo& info)
{
    auto end = info.getMovedUnits().end();
    for (auto it = info.getMovedUnits().begin(); it != end; ++it)
    {
        Unit* u = *it;
        GenerateInRangeEvent eg{u};
        spatials.apply(&eg);
    }
}


Location Map::findNextDepositArea(Location center, Size toDeposit, int &r, int &sq)
{
    int x = (int) center.x;
    int y = (int) center.y;

    for (;;)
    {
        int length = 2*r;

        for (;sq<4*length;sq++)
        {
            if (!isObstructed(Area{
                        center.x + x,
                        center.y + y,
                        toDeposit.width,
                        toDeposit.height}))
            {
                return Location{center.x + x, center.y + y};
            }

            switch (sq/length)
            {
            case 0:
                y--; break;
            case 1:
                x--; break;
            case 2:
                y++; break;
            case 3:
                x++; break;
            default:
                std::cout << "This should not happen 20480986209845\n";
                exit(-1);
            }
        }

        x++;
        y++;
        r++;
        sq = 0;

        if (r > 2 * std::max(width, height))
        {
            std::cout << "Unable to place unit." << std::endl;
            exit(-1);
        }
    }
}



}

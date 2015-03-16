
#include "model/unit.h"

#include "ai/unit/unit_listener.h"


#include <algorithm>

namespace aoe
{


Unit::Unit(const UnitDescription* desc) : type{desc}, health{1} {}

Unit::~Unit() {}


void Unit::addListener(UnitListener* listener)
{
    listeners.push_back(listener);
}

void Unit::removeListener(UnitListener* listener)
{
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
    {
        listeners.erase(it);
    }
}

std::ostream& operator<<(std::ostream& out, const Unit& u)
{
    return  out << u.type->getName() << " at " << u.area;
}

int Unit::getImageId() const
{
    return type->getImageId();
}


Area& Unit::getArea()
{
    return area;
}

const Area& Unit::getArea() const
{
    return area;
}

void Unit::broadcastEvent(UnitEvent event, void *ptr)
{
    auto end = listeners.end();
    for (auto it = listeners.begin(); it != end; ++it)
    {
        (*it)->handleUnitEvent(event, ptr);
    }
}


void Unit::setHealthPercent(double h) { health = h; }
double Unit::getHealthPercent() const { return health; }


const UnitDescription* Unit::getType() { return type; }

}

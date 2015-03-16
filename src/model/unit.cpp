
#include "model/unit.h"

#include "ai/unit/unit_listener.h"


#include <algorithm>

namespace aoe
{


Unit::Unit(const UnitDescription* desc) : type{desc} {}

Unit::~Unit() {}


void Unit::add_listener(UnitListener* listener)
{
    listeners.push_back(listener);
}

void Unit::remove_listener(UnitListener* listener)
{
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end())
    {
        listeners.erase(it);
    }
}

std::ostream& operator<<(std::ostream& out, const Unit& u)
{
    return  out << u.type->get_name() << " at " << u.area;
}

int Unit::get_image_id() const
{
    return type->get_image_id();
}


Area& Unit::getArea()
{
    return area;
}

const Area& Unit::getArea() const
{
    return area;
}


double Unit::get_speed() const
{
    return type->get_speed();
}

}

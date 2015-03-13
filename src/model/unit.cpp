
#include "model/unit.h"

#include "ai/unit/unit_listener.h"

#include "task/task.h"

#include <algorithm>

namespace aoe
{


Unit::Unit(const UnitDescription* desc) : task{nullptr}, type{desc} {}

Unit::~Unit() {}


void Unit::take_turn()
{
    if (task != nullptr)
    {
        task->apply(listeners);
    }
}


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

void Unit::set_task(Task* atask)
{
    task = atask;
}

std::ostream& operator<<(std::ostream& out, const Unit& u)
{
    return  out << u.type->get_name() << " at " << u.area;
}

int Unit::get_image_id() const
{
    return type->get_image_id();
}

const Area& Unit::get_location() const
{
    return area;
}

void Unit::set_size(double width, double height)
{
    area.set_size(width, height);
}


void Unit::set_location(const Area& area_)
{
    area = area_;
}

void Unit::set_location(const Location& area_)
{
    area = area_;
}


}

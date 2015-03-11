
#include "model/unit.h"

#include "ai/unit/unit_listener.h"

#include "task/task.h"

#include <algorithm>


Unit::Unit(UnitDescription* desc) : task{nullptr}, type{desc} {}

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
    out << "location: " << u.area << '\n';
    return out;
}

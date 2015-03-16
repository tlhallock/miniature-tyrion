
#include "task/movable.h"
#include "ai/unit/unit_listener.h"
#include "model/unit.h"


#include <cmath>

namespace aoe
{
Move::Move(Unit* unit_) :
    Task{unit_},
    dest{nullptr}
{

}

Move::~Move() {}

void Move::setDestination(Location* dest)
{
    this->dest = dest;
}

void Move::apply()
{
    if (dest == nullptr)
    {
        return;
    }
    double speed = unit->getType()->getSpeed();

    double direction_x = dest->x - unit->getArea().x;
    double direction_y = dest->y - unit->getArea().y;

    double norm = sqrt(direction_x*direction_x + direction_y*direction_y);

    if (norm < speed)
    {
        unit->getArea() = *dest;

        unit->broadcastEvent(UnitEvent::movableArrived);
        return;
    }

    unit->getArea() =  Location{ unit->getArea().x + direction_x * speed / norm,
                                 unit->getArea().y + direction_y * speed / norm};
}


std::string Move::getDescription() const { return "moving torwards " /* + dest.x + "," + dest.y*/; }


}

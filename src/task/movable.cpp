
#include "task/movable.h"
#include "ai/unit/unit_listener.h"
#include "model/unit.h"
#include "model/engine.h"
#include "model/game.h"

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

void Move::apply(IterationInfo& info)
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

    Area newArea{ unit->getArea().x + direction_x * speed / norm,
                  unit->getArea().y + direction_y * speed / norm,
                  unit->getType()->getSize().width,
                  unit->getType()->getSize().height};

    if (info.getGame()->getMap().isObstructed(newArea))
    {
        return;
    }

    info.getGame()->getMap().remove(unit);
    unit->getArea() = newArea;
    info.getGame()->getMap().add(unit);
    info.unitMoved(unit);
}

std::string Move::getDescription() const { return "moving torwards " /* + dest.x + "," + dest.y*/; }


}

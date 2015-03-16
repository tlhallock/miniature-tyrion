
#include "task/movable.h"
#include "ai/unit/unit_listener.h"
#include "model/unit.h"


#include <cmath>

namespace aoe
{
Move::Move(Unit* unit_) :
    unit{unit_},
    dest{Location{unit_->getArea()}}
{

}

Move::~Move() {}

void Move::set_destination(const Location& dest)
{
    this->dest = dest;
}

void Move::apply()
{
    double speed = unit->get_speed();

    double direction_x = dest.x - unit->getArea().x;
    double direction_y = dest.y - unit->getArea().y;

    double norm = sqrt(direction_x*direction_x + direction_y*direction_y);

    if (norm < speed)
    {
        unit->getArea() = dest;

        for (auto it = unit->get_listeners().begin(); it!=unit->get_listeners().end(); ++it)
        {
            (*it)->movable_arrived();
        }
        return;
    }

    unit->getArea() =  Location{ unit->getArea().x + direction_x * speed / norm,
                                 unit->getArea().y + direction_y * speed / norm};
}
}


#include "task/movable.h"
#include "ai/unit/unit_listener.h"
#include "model/unit.h"


#include <cmath>

namespace aoe
{
Move::Move(Unit* unit_) :
    unit{unit_},
    dest{unit_->get_location()}
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

    double direction_x = dest.x - unit->get_location().x;
    double direction_y = dest.y - unit->get_location().y;

    double norm = sqrt(direction_x*direction_x + direction_y*direction_y);

    if (norm < speed)
    {
        unit->set_location(Location{dest.x, dest.y});

        for (auto it = unit->get_listeners().begin(); it!=unit->get_listeners().end(); ++it)
        {
            (*it)->movable_arrived();
        }
        return;
    }

    unit->set_location(Location{ unit->get_location().x + direction_x * speed / norm,
                                 unit->get_location().y + direction_y * speed / norm});
}
}

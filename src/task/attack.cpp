
#include "task/attack.h"
#include "model/unit.h"
#include "ai/unit/unit_listener.h"

namespace aoe
{


Attack::Attack(Unit* unit) :
    Task{unit},
    target{nullptr}
{

}


Attack::~Attack()
{

}



void Attack::set_target(Unit* unit)
{

}

void Attack::apply()
{
    if (target == nullptr)
    {
        return;
    }

    double range = unit->getType()->getRange();

    if (unit->getArea().distanceTo(target->getArea()) > range)
    {
        unit->broadcastEvent(UnitEvent::targetOutOfRange);
        return;
    }

    int tid = target->getType()->getId();
    int uid = unit->getType()->getId();
    double damage = unit->getType()->getDamage(tid);
    double resistance = target->getType()->getResistance(uid);


    double totalHealthPoints = unit->getType()->getHealth();
    double health = unit->getHealthPercent();
    health *= totalHealthPoints;
    health -= damage * resistance;
    health /= totalHealthPoints;
    if (health <= 0)
    {
        health = 0;
        target->broadcastEvent(UnitEvent::destructibleDied);
    }
    unit->setHealthPercent(health);
}



std::string Attack::getDescription() const
{
    return "Attack";
}

}

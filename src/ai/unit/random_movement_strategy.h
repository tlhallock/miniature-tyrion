#ifndef RANDOM_MOVEMENT_STRATEGY_H
#define RANDOM_MOVEMENT_STRATEGY_H

#include "ai/unit/unit_strategy.h"
#include "model/spc/area.h"
#include "task/movable.h"

#include <memory>

namespace aoe
{

class Unit;
class Engine;

class RandomMovementStrategy : public UnitStrategy
{
private:
    Unit* unit;
    Area bounds;
    Location nextDest;
    Move moveTask;

public:
    RandomMovementStrategy(Engine* engine, Unit* unit, const Area& bounds);

    void movableArrived();

private:
    Location getNextLocation() const;
};



}

#endif // RANDOM_MOVEMENT_STRATEGY_H

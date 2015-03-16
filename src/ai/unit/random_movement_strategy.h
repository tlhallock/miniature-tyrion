#ifndef RANDOM_MOVEMENT_STRATEGY_H
#define RANDOM_MOVEMENT_STRATEGY_H

#include "ai/unit/unit_listener.h"
#include "model/spc/area.h"
#include "task/task.h"

#include <memory>

namespace aoe
{

class Unit;
class Engine;

class RandomMovementStrategy : public UnitListener
{
private:
    Engine* engine;
    Unit* unit;
    Area bounds;
    Area nextDest;
    std::unique_ptr<Task> previous;
public:
    RandomMovementStrategy(Engine* engine, Unit* unit, const Area& bounds);
    ~RandomMovementStrategy();

    void movableArrived();
};



}

#endif // RANDOM_MOVEMENT_STRATEGY_H

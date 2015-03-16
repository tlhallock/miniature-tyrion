#include "ai/unit/random_movement_strategy.h"
#include "model/unit.h"
#include "task/movable.h"
#include "model/engine.h"

namespace aoe
{

RandomMovementStrategy::RandomMovementStrategy(Engine* engine_, Unit* unit, const Area& bounds_) :
    UnitStrategy{engine_, unit},
    unit{unit},
    bounds{bounds_},
    nextDest{getNextLocation()},
    moveTask{unit}
{
    moveTask.setDestination(&nextDest);

    engine->addTask(&moveTask);
}

void RandomMovementStrategy::movableArrived()
{
    nextDest = getNextLocation();
}

Location RandomMovementStrategy::getNextLocation() const
{
    return Location{
            bounds.x + (rand() / (double) RAND_MAX) * bounds.width,
            bounds.y + (rand() / (double) RAND_MAX) * bounds.height};
}

}

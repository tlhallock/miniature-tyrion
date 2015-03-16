#include "ai/unit/random_movement_strategy.h"
#include "model/unit.h"
#include "task/movable.h"
#include "model/engine.h"

namespace aoe
{


RandomMovementStrategy::RandomMovementStrategy(Engine* engine_, Unit* unit, const Area& bounds_) :
    engine{engine_},
    unit{unit},
    bounds{bounds_},
    nextDest{}
{
    movableArrived();
    unit->addListener(this);

    Move* next_task = new Move{unit};
    next_task->setDestination(&nextDest);
    previous = std::unique_ptr<Task>{next_task};
    engine->addTask(next_task);
}

RandomMovementStrategy::~RandomMovementStrategy()
{
    unit->removeListener(this);
    engine->idle(unit);
}


void RandomMovementStrategy::movableArrived()
{
    nextDest = Location{
            bounds.x + (rand() / (double) RAND_MAX) * bounds.width,
            bounds.y + (rand() / (double) RAND_MAX) * bounds.height};

}

}

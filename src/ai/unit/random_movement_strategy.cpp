#include "ai/unit/random_movement_strategy.h"
#include "model/unit.h"
#include "task/movable.h"
#include "model/engine.h"

namespace aoe
{


RandomMovementStrategy::RandomMovementStrategy(Engine* engine_, Unit* unit, const Area& bounds_) :
    engine{engine_},
    unit{unit},
    bounds{bounds_}
{
    unit->add_listener(this);
    movable_arrived();
}
RandomMovementStrategy::~RandomMovementStrategy()
{
    unit->remove_listener(this);
    engine->set_task(unit, nullptr);
}


void RandomMovementStrategy::movable_arrived()
{
    Move* next_task = new Move{unit};
    next_task->set_destination(Location{
        bounds.x + (rand() / (double) RAND_MAX) * bounds.w,
        bounds.y + (rand() / (double) RAND_MAX) * bounds.h});

    engine->set_task(unit, next_task);
    previous = std::unique_ptr<Task>{next_task};
}

}

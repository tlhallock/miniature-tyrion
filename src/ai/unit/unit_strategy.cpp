#include "ai/unit/unit_strategy.h"

#include "model/unit.h"
#include "model/engine.h"

namespace aoe
{


UnitStrategy::UnitStrategy(Engine* engine_, Unit* unit_) :
    engine{engine_},
    unit{unit_}
{
    if (unit != nullptr)
    {
        unit->addListener(this);
    }
}

UnitStrategy::~UnitStrategy()
{
    if (unit != nullptr)
    {
        unit->removeListener(this);
        engine->idle(unit);
    }
}


}

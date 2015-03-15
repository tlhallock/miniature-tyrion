#include "ai/player/ai_strategy.h"
#include "ai/unit/random_movement_strategy.h"
#include "main/settings.h"
#include "model/engine.h"
#include "model/unit.h"

namespace aoe
{

AiStrategy::AiStrategy(Engine* engine_) :
    engine{engine_}
{
}

void AiStrategy::unit_created(Unit* u)
{
    const std::string& name = u->get_type()->get_name();
    if (name == "villager")
    {
        new RandomMovementStrategy{engine, u, Area{0, 0, Settings::get_instance().MAP_WIDTH, Settings::get_instance().MAP_HEIGHT}};
    }
}


}


#include "ai/unit/unit_listener.h"

#include "model/unit.h"

namespace aoe
{

UnitListener::UnitListener() {}
UnitListener::~UnitListener() {}


void UnitListener::movable_arrived() {}

void UnitListener::collector_full() {}
void UnitListener::collector_empty() {}

void UnitListener::destructible_died() {}
void UnitListener::attacker_killed() {}

void UnitListener::enemy_in_rage(Unit *enemy) {}

}

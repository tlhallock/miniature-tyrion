#include "player_listener.h"

#include "res/resource_descp.h"
#include "res/technology.h"

#include "model/unit.h"
#include "model/building.h"

namespace aoe
{

PlayerListener::PlayerListener() {}
PlayerListener::~PlayerListener() {}

void PlayerListener::resource_changed(ResourceDescription* desc) {}

void PlayerListener::unit_created(Unit* u) {}
void PlayerListener::unit_killed(Unit* u) {}

void PlayerListener::building_built(Building* b) {}
void PlayerListener::building_destroyed(Building* b) {}

void PlayerListener::technology_researched(Technology* t) {}

}

#include "generator.h"

#include "model/game.h"
#include "model/civilization.h"
#include "model/unit.h"
#include "model/player.h"

namespace aoe
{



void generate_map(Game* game)
{
    Player *player = game->get_player(0);
    Civilization* civilization = player->get_civilization();

    int building_id = game->get_table().get_building_id("town center");
    civilization->create_building(building_id, player->get_location());


}

}

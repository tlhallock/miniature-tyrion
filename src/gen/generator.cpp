#include "generator.h"

#include "model/game.h"
#include "model/civilization.h"
#include "model/unit.h"
#include "model/player.h"

namespace aoe
{



void generate_map(Game* game)
{
    std::cout << "Generating the map..." << std::endl;


    Player *player = game->get_player(0);
    Civilization* civilization = player->get_civilization();

    int building_id = game->get_table().get_building_id("town center");
    Unit* town_center = civilization->create_building(building_id, Location{player->get_location()}, true);
    if (town_center == nullptr)
    {
        std::cerr << "Unable to create town center" << std::endl;
        exit(-1);
    }

    game->get_map().place_unit(town_center);

}

}

#include "player.h"


#include "model/civilization.h"
#include "res/civilization_descp.h"
#include "res/game_info.h"

#include "model/unit.h"
#include "model/building.h"

namespace aoe
{

Player::Player(GameInfo* info, int index) :
    resources{new int[info->get_number_of_resources()]}
{

}



Player::~Player()
{
    delete[] resources;
}

}

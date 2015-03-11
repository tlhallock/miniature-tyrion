#include "player.h"


#include "model/civilization.h"
#include "res/civilization_descp.h"
#include "res/game_info.h"

#include "model/unit.h"
#include "model/building.h"

Player::Player(GameInfo* info, int index) :
    civilization{desc->create()},
    resources{new int[nres]}
{
}

Player::~Player()
{
    delete[] resources;
}

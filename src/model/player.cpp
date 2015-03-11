#include "player.h"


#include "model/civilization.h"
#include "res/civilization_descp.h"

#include "model/unit.h"
#include "model/building.h"

Player::Player(CivilizationDescription* desc, int nres) :
    civilization{desc->create()},
    resources{new int[nres]}
{
}

Player::~Player()
{
    delete[] resources;
}

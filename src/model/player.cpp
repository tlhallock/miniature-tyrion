#include "player.h"


#include "ai/player/player_listener.h"
#include "model/civilization.h"
#include "res/civilization_descp.h"
#include "res/game_info.h"

#include "model/unit.h"
#include "model/building.h"

namespace aoe
{

Player::Player(Civilization* civ, const std::vector<double>& res, const Location& center_) :
    civilization{civ},
    resources{res},
    center{center_}
{

}

Player::~Player() {}



void Player::add_listener(PlayerListener* listener)
{
    listeners.push_back(listener);
}

void Player::remove_listener(PlayerListener* listener)
{
    for (auto it = listeners.begin(); it != listeners.end(); ++it)
    {
        if (*it == listener)
        {
            listeners.erase(it);
            return;
        }
    }
}


Civilization* Player::get_civilization()
{
    return civilization.get();
}



const Location& Player::get_location()
{
    return center;
}


void Player::unit_added(Unit* unit)
{
    units.push_back(unit);

    for (auto it = listeners.begin(); it != listeners.end(); ++it)
    {
        (*it)->unit_created(unit);
    }
}

}



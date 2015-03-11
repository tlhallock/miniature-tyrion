
#include "model/game.h"

#include "model/map.h"
#include "model/player.h"

#include "ai/player/strategy.h"

#define CLOCK_FREQ 200

Game::Game() :
    map{},
    engine{},
    timer{CLOCK_FREQ} {}

Game::~Game() {}


void Game::add_player(Strategy* strategy, Player *player)
{

}

Map& Game::get_map()
{
    return map;
}

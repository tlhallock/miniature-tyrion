
#include "model/game.h"

#include "model/map.h"
#include "model/player.h"

#include "ai/player/strategy.h"

namespace aoe
{

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

Engine& Game::get_engine()
{
    return engine;
}

Timer& Game::get_timer()
{
    return timer;
}

}

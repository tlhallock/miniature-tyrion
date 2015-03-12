
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
    timer{CLOCK_FREQ}
{
    timer.add(&engine);
}

Game::~Game() {}


void Game::add_player(Strategy* strategy, Player *player)
{
     players.push_back(std::unique_ptr<Player>{player});
     strategies.push_back(std::unique_ptr<Strategy>{strategy});

     player->add_listener(this);
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


void Game::start()
{
    timer.start();
}
void Game::end()
{
    timer.end();
}

void Game::unit_created(Unit* u)
{
    map.place_unit(u);
}

void Game::unit_killed(Unit* u)
{
    map.remove_unit(u);
}



}

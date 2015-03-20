
#include "model/game.h"

#include "model/map.h"
#include "model/player.h"
#include "main/settings.h"
#include "model/engine.h"

#include "ai/player/strategy.h"

#define DEBUG_MAP 0


namespace aoe
{

Game::Game(const IdentifierTable& table_) :
    map{},
    engine{},
    table{table_},
    itInfo{this} {}

Game::~Game() {}


void Game::add_player(Strategy* strategy, Player *player)
{
     players.push_back(std::unique_ptr<Player>{player});
     strategies.push_back(std::unique_ptr<Strategy>{strategy});

     player->add_listener(strategy);
     player->add_listener(this);
}

Map& Game::getMap()
{
    return map;
}

Engine& Game::get_engine()
{
    return engine;
}

void Game::unit_created(Unit* u)
{
    map.add(u);
}

void Game::unit_killed(Unit* u)
{
    map.remove(u);
}

Player* Game::get_player(int index)
{
       return players[index].get();
}


IdentifierTable& Game::get_table()
{
    return table;
}


std::ostream& operator<<(std::ostream& out, const Game& g)
{
    out << "Map:\n";
    out << g.map;
    return out;
}

void Game::run()
{
    engine.animateIteration(itInfo);
    map.generateRangeNotifications(itInfo);
    itInfo.reset();

#if DEBUG_MAP
            std::cout << *this << std::endl;
#endif


}

}

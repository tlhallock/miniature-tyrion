
#include "model/game.h"

#include "model/map.h"
#include "model/player.h"
#include "main/settings.h"

#include "ai/player/strategy.h"

namespace aoe
{


namespace
{

    class PrintTask : public TimerTask
    {
    private:
        Game* game;

    public:
        PrintTask(Game* game_) :
            game{game_} {}
        ~PrintTask() {}

        void run()
        {
//            std::cout << *game << std::endl;
        }
    };
}

Game::Game(const IdentifierTable& table_) :
    map{},
    engine{},
    timer{Settings::get_instance().EGNINE_CLOCK_FREQ},
    table{table_}
{
    timer.add(&engine);
    timer.add(new PrintTask{this});
}

Game::~Game() {}


void Game::add_player(Strategy* strategy, Player *player)
{
     players.push_back(std::unique_ptr<Player>{player});
     strategies.push_back(std::unique_ptr<Strategy>{strategy});

     player->add_listener(strategy);
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


}

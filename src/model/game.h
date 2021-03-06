

#ifndef GAME_H_
#define GAME_H_

#include <memory>

#include "model/map.h"
#include "model/engine.h"
#include "util/timer.h"
#include "ai/player/player_listener.h"
#include "res/identifier_table.h"

namespace aoe
{

class Player;
class Strategy;

class Game : public PlayerListener, public TimerTask
{
private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Strategy>> strategies;

    Map map;
    Engine engine;
    IdentifierTable table;

    IterationInfo itInfo;
public:
    Game(const IdentifierTable& table);
    ~Game();
  
    void add_player(Strategy* strategy, Player *player);

    Map& getMap();
    Engine& get_engine();
    Timer& get_timer();

    void start();
    void end();

    void unit_created(Unit* u);
    void unit_killed(Unit* u);

    int get_num_players() { return players.size(); }
    Player* get_player(int index);

    IdentifierTable& get_table();

    friend std::ostream& operator<<(std::ostream& out, const Game& g);

    void run();

};

}

#endif

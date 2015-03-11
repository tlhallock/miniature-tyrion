

#ifndef GAME_H_
#define GAME_H_

#include <memory>

#include "model/map.h"
#include "model/engine.h"
#include "util/timer.h"

class Player;
class Strategy;

class Game
{
private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Strategy>> strategies;

    Map map;
    Engine engine;
    Timer timer;

public:
    Game();
    ~Game();
  
    void add_player(Strategy* strategy, Player *player);

    Map& get_map();
};


#endif

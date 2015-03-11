#ifndef STRATEGY_H
#define STRATEGY_H

namespace aoe
{

class Player;

class Strategy
{
private:
    Player *player;

public:
    Strategy(Player* player);
    ~Strategy();
};

}

#endif // STRATEGY_H

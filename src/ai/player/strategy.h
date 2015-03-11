#ifndef STRATEGY_H
#define STRATEGY_H

class Player;

class Strategy
{
private:
    Player *player;

public:
    Strategy(Player* player);
    ~Strategy();
};

#endif // STRATEGY_H

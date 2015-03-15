#ifndef STRATEGY_H
#define STRATEGY_H

#include "ai/player/player_listener.h"

namespace aoe
{


class Strategy : public PlayerListener
{
private:
public:
    Strategy();
    ~Strategy();
};

}

#endif // STRATEGY_H

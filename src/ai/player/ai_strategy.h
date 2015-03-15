#ifndef AISTRATEGY_H
#define AISTRATEGY_H

#include "ai/player/strategy.h"

namespace aoe
{

class Engine;

class AiStrategy : public Strategy
{
private:
    Engine *engine;
public:
    AiStrategy(Engine* engine);

    void unit_created(Unit* u);
};

}

#endif // AISTRATEGY_H

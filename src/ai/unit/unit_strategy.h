#ifndef UNIT_STRATEGY_H
#define UNIT_STRATEGY_H

#include "ai/unit/unit_listener.h"

namespace aoe
{

class Engine;

class UnitStrategy : public UnitListener
{
protected:
    Engine* engine;
    Unit* unit;
public:
    UnitStrategy(Engine* engine, Unit* unit);
    virtual ~UnitStrategy();
};

}

#endif // UNIT_STRATEGY_H

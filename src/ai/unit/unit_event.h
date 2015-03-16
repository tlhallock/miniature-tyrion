#ifndef UNIT_EVENT_H
#define UNIT_EVENT_H

namespace aoe
{

enum UnitEvent
{
    movableObstructed,
    movableArrived,
    collectorFull,
    collectorEmpty,
    destructibleDied,
    targetOutOfRange,
    targetKilled,
    enemyInRange,
};

}

#endif // UNIT_EVENT_H

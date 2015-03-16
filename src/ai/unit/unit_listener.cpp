
#include "ai/unit/unit_listener.h"

#include "model/unit.h"

namespace aoe
{

UnitListener::UnitListener() {}
UnitListener::~UnitListener() {}


void UnitListener::handleUnitEvent(UnitEvent event, void* ptr)
{
  switch (event)
  {
    case UnitEvent::movableObstructed: movableObstructed();   return;
    case UnitEvent::movableArrived:    movableArrived();      return;
    case UnitEvent::collectorFull:     collectorFull();       return;
    case UnitEvent::collectorEmpty:    collectorEmpty();      return;
    case UnitEvent::destructibleDied:  destructibleDied();    return;
    case UnitEvent::targetOutOfRange:  targetOutOfRange();    return;
    case UnitEvent::targetKilled:      targetKilled();        return;
    case UnitEvent::enemyInRange:      enemyInRange((Unit*) ptr); return;
  default:
      std::cerr << "Unkown message type: " << event << std::endl;
      exit(-1);
  }
}

void UnitListener::movableObstructed() {}
void UnitListener::movableArrived() {}
void UnitListener::collectorFull() {}
void UnitListener::collectorEmpty() {}
void UnitListener::destructibleDied() {}
void UnitListener::targetOutOfRange() {}
void UnitListener::targetKilled() {}
void UnitListener::enemyInRange(Unit *enemy) {}

}

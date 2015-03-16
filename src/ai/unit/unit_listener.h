

#ifndef TASK_LISTENER_H_
#define TASK_LISTENER_H_

#include "ai/unit/unit_event.h"

namespace aoe
{

class Unit;

class UnitListener
{
 public:
  UnitListener();
  virtual ~UnitListener();

  void handleUnitEvent(UnitEvent event, void*ptr=nullptr);

  virtual void movableObstructed();
  virtual void movableArrived();

  virtual void collectorFull();
  virtual void collectorEmpty();

  virtual void destructibleDied();

  virtual void targetOutOfRange();
  virtual void targetKilled();

  virtual void enemyInRange(Unit *enemy);
};


}


#endif

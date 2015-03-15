

#ifndef TASK_LISTENER_H_
#define TASK_LISTENER_H_

namespace aoe
{

class Unit;

class UnitListener
{
 public:
  UnitListener();
  virtual ~UnitListener();

  virtual void movable_arrived();

  virtual void collector_full();
  virtual void collector_empty();

  virtual void destructible_died();
  virtual void attacker_killed();

  virtual void enemy_in_rage(Unit *enemy);
};


}


#endif

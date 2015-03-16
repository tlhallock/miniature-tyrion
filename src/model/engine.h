


#ifndef ENGINE_H_
#define ENGINE_H_

#include <map>
#include <iostream>

#include "util/timer.h"

namespace aoe
{

class Task;
class Unit;

class Engine : public TimerTask
{
 private:
  std::map<Unit*, Task*> active_units;

 public:
  Engine();
  ~Engine();


  void addTask(Task* Unit);
  void idle(Unit* unit);

  friend std::ostream& operator<<(std::ostream& out, const Engine& e);

  void run();


private:
  void animateIteration();
};

}


#endif

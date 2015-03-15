


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

  void animate_iteration();

  void set_task(Unit* unit, Task* Unit);

//  bool contains(Task* Unit);

  friend std::ostream& operator<<(std::ostream& out, const Engine& e);

  void run();
};

}


#endif

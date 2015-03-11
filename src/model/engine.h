


#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>

#include "util/timer.h"

namespace aoe
{

class Unit;

class Engine : public TimerTask
{
 private:
  std::vector<Unit*> active_units;

 public:
  Engine();
  ~Engine();

  void animate_iteration();

  void add_unit(Unit* Unit);
  void remove_unit(Unit* Unit);

  bool contains(Unit* Unit);

  friend std::ostream& operator<<(std::ostream& out, const Engine& e);

  void run();
};

}


#endif

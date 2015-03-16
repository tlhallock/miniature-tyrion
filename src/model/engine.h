


#ifndef ENGINE_H_
#define ENGINE_H_

#include <map>
#include <iostream>
#include <set>

namespace aoe
{

class Task;
class Unit;

class Engine
{
 private:
  std::map<Unit*, Task*> active_units;

 public:
  Engine();

  void addTask(Task* Unit);
  void idle(Unit* unit);
  void animateIteration(std::set<Unit*>& movedUnits);

  friend std::ostream& operator<<(std::ostream& out, const Engine& e);


};

}


#endif

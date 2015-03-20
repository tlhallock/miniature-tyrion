


#ifndef ENGINE_H_
#define ENGINE_H_

#include <map>
#include <iostream>
#include <set>

namespace aoe
{

class Task;
class Unit;
class Game;

class IterationInfo
{
private:
    std::set<Unit*> movingUnits;
    Game* game;
//    std::map<Location, Location> attacks;
public:
    IterationInfo(Game* game);

    void reset();

    void unitMoved(Unit* u);
    const std::set<Unit*>& getMovedUnits() const;
    Game* getGame() const;
};


class Engine
{
 private:
  std::map<Unit*, Task*> active_units;

 public:
  Engine();

  void addTask(Task* Unit);
  void idle(Unit* unit);
  void animateIteration(IterationInfo& info);

  friend std::ostream& operator<<(std::ostream& out, const Engine& e);


};

}


#endif

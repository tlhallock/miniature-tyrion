


#ifndef UNIT_H_
#define UNIT_H_

#include <vector>

#include "model/area.h"

#include "res/unit_descp.h"

class UnitListener;
class Task;
class Player;
class UnitDescription;

class Unit
{
 private:
  Area area;
  std::vector<UnitListener*> listeners;
  Task* task;
  UnitDescription *type;
  Player *parent;
  
 public:
  Unit(UnitDescription* desc);
  ~Unit();

  void take_turn();

  void add_listener(UnitListener* listener);
  void remove_listener(UnitListener* listener);

  void set_task(Task* task);

  friend std::ostream& operator<<(std::ostream& out, const Unit& u);
};


#endif

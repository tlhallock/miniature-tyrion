


#ifndef UNIT_H_
#define UNIT_H_

#include <vector>

#include "model/area.h"
#include "res/unit_descp.h"

#include "gfx/gfx.h"

class UnitListener;
class Task;
class Player;
class UnitDescription;

class Unit : public Gfx
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


  int get_image_id() const;
  const Area& get_location() const;
};


#endif

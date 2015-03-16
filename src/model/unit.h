


#ifndef UNIT_H_
#define UNIT_H_

#include <vector>

#include "model/spc/area.h"
#include "res/unit_descp.h"

#include "gfx/gfx.h"

namespace aoe
{

class UnitListener;
class Player;
class UnitDescription;

class Unit : public Gfx
{
 private:
  Area area;
  std::vector<UnitListener*> listeners;
  const UnitDescription *type;
  
 public:
  Unit(const UnitDescription* desc);
  ~Unit();

  const UnitDescription* get_type() { return type; }

  void add_listener(UnitListener* listener);
  void remove_listener(UnitListener* listener);
  std::vector<UnitListener*>& get_listeners() { return listeners; }

  void setArea(const Area& area);
  Area& getArea();
  const Area& getArea() const;

  double get_speed() const;

  friend std::ostream& operator<<(std::ostream& out, const Unit& u);

  int get_image_id() const;
};

}


#endif

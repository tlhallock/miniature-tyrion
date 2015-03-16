


#ifndef UNIT_H_
#define UNIT_H_

#include <vector>

#include "model/spc/area.h"
#include "res/unit_descp.h"
#include "ai/unit/unit_event.h"

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
  double health;
  
 public:
  Unit(const UnitDescription* desc);
  ~Unit();

  const UnitDescription* getType();

  void addListener(UnitListener* listener);
  void removeListener(UnitListener* listener);
  void broadcastEvent(UnitEvent event);

  void setArea(const Area& area);
  Area& getArea();
  const Area& getArea() const;

  friend std::ostream& operator<<(std::ostream& out, const Unit& u);

  void setHealthPercent(double h);
  double getHealthPercent() const;

  int getImageId() const;
};

}


#endif

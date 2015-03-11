

#include "model/area.h"

#include <cmath>

double Area::distance_to(const Area& other) const
{
  double dx = x - other.x;
  double dy = y - other.y;
  return std::sqrt(dx*dx + dy*dy);
}

bool Area::contains(const Area& other) const
{
  return 
    x < other.x && y < other.y &&
       x + w > other.x && y + h > other.y;
}


std::ostream& operator<<(std::ostream& out, const Area& a)
{
  return out << "[(" << a.x << "," << a.y <<")-(" << (a.x + a.w) << "," << (a.y + a.h) << ")]";
}

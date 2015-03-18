
#include "model/spc/area.h"

//#include <cmath>

namespace aoe
{


Area::Area() :
    Location{0, 0},
    Size{0, 0} {}

Area::Area(double mx, double my, double mw, double mh) :
   Location{mx, my},
   Size{mw, mh} {}


//double Area::distance_to(const Area& other) const
//{
//  double dx = x - other.x;
//  double dy = y - other.y;
//  return std::sqrt(dx*dx + dy*dy);
//}

bool Area::contains(const Area& other) const
{
    std::cout << "Fix method area::contains" << std::endl;
  return 
    x < other.x && y < other.y &&
       x + width > other.x && y + height > other.y;
}

//void Area::set_size(double width, double height)
//{
//    w = width;
//    h = height;
//}


//Area& Area::operator=(const Location& loc)
//{
//    x = loc.x;
//    y = loc.y;
//    return *this;
//}

std::ostream& operator<<(std::ostream& out, const Area& a)
{
  return out << "[(" << a.x << "," << a.y <<")-(" << (a.x + a.width) << "," << (a.y + a.height) << ")]";
}


bool Area::overlaps(const Area& r) const
{
    double tw = this->width;
    double th = this->height;
    double rw = r.width;
    double rh = r.height;
    if (rw < 0 || rh < 0 || tw < 0 || th < 0)
    {
        return false;
    }
    double tx = this->x;
    double ty = this->y;
    double rx = r.x;
    double ry = r.y;
    rw += rx;
    rh += ry;
    tw += tx;
    th += ty;

    return ((rw < rx || rw > tx) &&
            (rh < ry || rh > ty) &&
            (tw < tx || tw > rx) &&
            (th < ty || th > ry));
}


Area& Area::operator=(const Location& loc)
{
    x = loc.x;
    y = loc.y;
    return *this;
}

Area& Area::operator=(const Size& size)
{
    width = size.width;
    height = size.height;
    return *this;
}



}


#include "model/spc/area.h"

#include <cmath>

namespace aoe
{


Area::Area() :
    Location{0, 0},
    Size{0, 0} {}

Area::Area(double mx, double my, double mw, double mh) :
   Location{mx, my},
   Size{mw, mh} {}

bool Area::contains(const Area& other) const
{
    std::cout << "Fix method area::contains" << std::endl;
  return 
    x < other.x && y < other.y &&
       x + width > other.x && y + height > other.y;
}


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


double Area::distanceTo(const Location& other) const
{
    double dx = 0;
    if (other.x > x + width)
    {
        dx = other.x - (x + width);
    }
    else if (other.x < x)
    {
        dx = x - other.x;
    }
    else
    {
        dx = 0;
    }

    double dy = 0;
    if (other.y > y + height)
    {
        dy = other.y - (y + height);
    }
    else if (other.y < y)
    {
        dy = y - other.y;
    }
    else
    {
        dy = 0;
    }

    return sqrt(dx*dx+dy*dy);
}

double Area::distanceTo(const Area& other) const
{
    // TODO: fix this!!!!

    double dx = 0;
    if (other.x > x + width)
    {
        dx = other.x - (x + width);
    }
    else if (other.x < x)
    {
        dx = x - other.x;
    }
    else
    {
        dx = 0;
    }

    double dy = 0;
    if (other.y > y + height)
    {
        dy = other.y - (y + height);
    }
    else if (other.y < y)
    {
        dy = y - other.y;
    }
    else
    {
        dy = 0;
    }

    return sqrt(dx*dx+dy*dy);
}



}



#include "model/area.h"

#include <cmath>

namespace aoe
{

Location::Location() : x{0}, y{0} {}

Location::Location(double x_, double y_) : x{x_}, y{y_} {}
Location::Location(const Area& a) : Location{a.x, a.y} {}

void Location::setX(double x_)
{
    x = x_;
}
void Location::setY(double y_)
{
    y = y_;
}

double Location::getX()
{
    return x;
}
double Location::getY()
{
    return y;
}

void Location::set(double x_, double y_)
{
    x = x_;
    y = y_;
}

double Location::distance_to(const Location& other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx*dx + dy*dy);
}

Location& Location::operator=(const Area& a)
{
    x = a.x;
    y = a.y;
    return *this;
}



bool LocationCmp::operator() (const Location& l1, const Location& l2)
{
    if (l1.x == l2.x)
    {
        return l1.y < l2.y;
    }
    else
    {
        return l1.x < l2.x;
    }
}


Location Location::operator/(double d) const
{
    return Location{x / d, y / d};
}

std::ostream& operator<<(std::ostream& out, const Location& a)
{
    return out << "[" << a.x << "," << a.y << "]";
}



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

void Area::set_size(double width, double height)
{
    w = width;
    h = height;
}


Area& Area::operator=(const Location& loc)
{
    x = loc.x;
    y = loc.y;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Area& a)
{
  return out << "[(" << a.x << "," << a.y <<")-(" << (a.x + a.w) << "," << (a.y + a.h) << ")]";
}


bool Area::overlaps(const Area& r) const
{
    double tw = this->w;
    double th = this->h;
    double rw = r.w;
    double rh = r.h;
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




}

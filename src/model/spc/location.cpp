#include "location.h"

#include <cmath>

namespace aoe
{

Location::Location() : x{0}, y{0} {}

Location::Location(double x_, double y_) : x{x_}, y{y_} {}
//Location::Location(const Area& a) : Location{a.x, a.y} {}


Location::~Location() {}

void Location::setX(double x_)
{
    x = x_;
}
void Location::setY(double y_)
{
    y = y_;
}

double Location::getX() const
{
    return x;
}
double Location::getY() const
{
    return y;
}

void Location::setLocation(double x_, double y_)
{
    x = x_;
    y = y_;
}

double Location::distanceTo(const Location& other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx*dx + dy*dy);
}

//Location& Location::operator=(const Area& a)
//{
//    x = a.x;
//    y = a.y;
//    return *this;
//}



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

Location Location::operator*(double d) const
{
    return Location{x * d, y * d};
}

std::ostream& operator<<(std::ostream& out, const Location& a)
{
    return out << "[" << a.x << "," << a.y << "]";
}

}

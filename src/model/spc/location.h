#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

namespace aoe
{

//class Area;

class Location
{
public:
    double x, y;

    Location();
    Location(double x, double y);
//    Location(const Area& a);

    virtual ~Location();

//    Location& operator=(const Area& a);
    Location operator/(double d) const;
    Location operator*(double d) const;

    void setX(double x);
    void setY(double y);

    double getX() const;
    double getY() const;

    void setLocation(double x, double y);
    double distance_to(const Location& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Location& a);
};


struct LocationCmp
{
    bool operator() (const Location& l1, const Location& l2);
};


}

#endif // LOCATION_H


#ifndef AREA_H_
#define AREA_H_

#include <iostream>

namespace aoe
{

class Area;

class Location
{
public:
    double x, y;

    Location();
    Location(double x, double y);
    Location(const Area& a);

    Location& operator=(const Area& a);
    Location operator/(double d) const;

    void setX(double x);
    void setY(double y);

    double getX();
    double getY();

    void set(double x, double y);
    double distance_to(const Location& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Location& a);
};

struct LocationCmp
{
    bool operator() (const Location& l1, const Location& l2);
};

class Area
{
 public:
  double x, y;
  double w, h;

 Area() :
    x{0}, y{0},
    w{0}, h{0} {}

 Area(double mx, double my, double mw, double mh) :
    x{mx}, y{my},
    w{mw}, h{mh} {}

    Area& operator=(const Location& loc);

    double distance_to(const Area& other) const;
    bool   contains(const Area& other) const;
    void   set_size(double width, double height);

    friend std::ostream& operator<<(std::ostream& out, const Area& a);
};


}

#endif

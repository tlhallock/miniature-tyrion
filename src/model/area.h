
#ifndef AREA_H_
#define AREA_H_

#include <iostream>

namespace aoe
{

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
      

    double distance_to(const Area& other) const;
    bool   contains(const Area& other) const;


    friend std::ostream& operator<<(std::ostream& out, const Area& a);
};


}

#endif

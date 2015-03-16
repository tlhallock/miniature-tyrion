
#ifndef AREA_H_
#define AREA_H_

#include "model/spc/location.h"
#include "model/spc/size.h"

namespace aoe
{

class Area : public Location, public Size
{
 public:

 Area();
 Area(double mx, double my, double mw, double mh);

    Area& operator=(const Location& loc);
    Area& operator=(const Size& size);

    double distance_to(const Area& other) const;
    bool   contains(const Area& other) const;

    bool overlaps(const Area& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Area& a);
};


}

#endif

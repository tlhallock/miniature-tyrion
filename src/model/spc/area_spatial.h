#ifndef AREA_SPATIAL_H
#define AREA_SPATIAL_H

#include "model/spc/area.h"
#include "model/spc/spatial.h"

namespace aoe
{

class SimpleSpatial : public Spatial
{
private:
    Area area;
public:
    SimpleSpatial(const Area& area_) : area{area_} {}
    virtual ~SimpleSpatial() {}

    Area& getArea() { return area; }

    SpatialType getSpatialType() const { return TEMPORARY; }
    std::string getSpatialDescription() const { return "tmp"; }
};

}

#endif // AREA_SPATIAL_H

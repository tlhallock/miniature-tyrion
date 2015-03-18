#ifndef SPATIAL_H
#define SPATIAL_H

#include <string>

namespace aoe
{
class Area;

enum SpatialType
{
    UNIT_TYPE,
    BUILDING_TYPE,
    RESOURCE_TYPE,
    TEMPORARY,
};

class Spatial
{
public:
    Spatial() {}
    virtual ~Spatial() {}

    virtual Area& getArea() = 0;

    virtual SpatialType getSpatialType() const = 0;
    virtual std::string getSpatialDescription() const = 0;
};


}
#endif // SPATIAL_H

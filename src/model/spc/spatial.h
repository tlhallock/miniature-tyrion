#ifndef SPATIAL_H
#define SPATIAL_H
namespace aoe
{
class Area;

class Spatial
{
public:
    Spatial() {}
    virtual ~Spatial() {}

    virtual const Area& getArea() = 0;
};
}
#endif // SPATIAL_H

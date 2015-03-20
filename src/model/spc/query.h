#ifndef QUERY_H
#define QUERY_H

#include "model/spc/area.h"

namespace aoe
{

#define TOLERANCE .000000001
#define IsZero(x)    ( ((x)<0) ? (x) > -TOLERANCE : (x) < TOLERANCE)
#define getXCoord(x) ((int) (x))
#define getYCoord(y) ((int) (y))

class Spatial;
class Square;



class Query
{
public:
    Area center;
    double radius;

    Query(const Area& c, double r) : center{c}, radius{std::max(r, TOLERANCE)} {}
    virtual ~Query() {}

    virtual bool includes(int x, int y)
    {
        return center.distanceTo(Location{x, y}) <= radius;
    }
    virtual bool createOnEmpty() const { return false; }
};

class SpatialQuery : public Query
{
public:
    SpatialQuery(const Area& c, double r) : Query{c, r} {}
    virtual ~SpatialQuery() {}

    virtual void apply(Spatial* sp) = 0;
};
class SquareQuery : public Query
{
public:
    SquareQuery(const Area& c, double r) : Query{c, r} {}
    virtual ~SquareQuery() {}
    virtual void apply(Square* sp) = 0;
};

}

#endif // QUERY_H

#ifndef GRID_H
#define GRID_H

namespace aoe
{

class XVals;
class SpatialQuery;
class SquareQuery;
class Spatial;

class Grid
{
private:
    XVals *xvals;
public:
    Grid();
    ~Grid();

    void remove(Spatial* a);
    void add(Spatial* a);

    bool overlaps(Spatial* sp);

    void apply(SpatialQuery*q);
    void apply(SquareQuery*q);
};


}


#endif // GRID_H

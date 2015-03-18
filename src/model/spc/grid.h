#ifndef GRID_H
#define GRID_H

#include <iostream>

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

    void collapseUnusedSquares();

    int count() const;

    friend std::ostream& operator<<(std::ostream& out, const Grid& g);
};


}


#endif // GRID_H

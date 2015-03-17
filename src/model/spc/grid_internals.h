#ifndef GRID_INTERNALS_H
#define GRID_INTERNALS_H

#include "model/spc/grid.h"
#include "model/spc/query.h"
#include "model/spc/spatial.h"

#include <set>

namespace aoe
{

#define TOLERANCE .00000000001
#define IsZero(x)    ( ((x)<0) ? (x) > -TOLERANCE : (x) < TOLERANCE)
#define getXCoord(x) ((int) (x))
#define getYCoord(y) ((int) (y))


class Square
{
private:
    std::set<Spatial*> spacials;

public:
    Square() {}
    ~Square() {}

    int size() { return spacials.size(); }

    void add(Spatial* sp)
    {
        spacials.insert(sp);
    }

    void remove(Spatial* sp)
    {
        auto it = spacials.find(sp);
        if (it != spacials.end())
        {
            spacials.erase(it);
        }
    }

    void apply(int x, int y, SpatialQuery*q)
    {
        auto begin = spacials.begin();
        auto end   = spacials.end();

        for (auto it = begin; it != end; ++it)
        {
            if (q->includes(x, y))
            {
                q->apply(*it);
            }
        }
    }
};


}

#endif // GRID_INTERNALS_H

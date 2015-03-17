
#include "model/spc/grid.h"

#include "model/spc/grid_internals.h"


#include <map>

namespace aoe
{

// TODO: Remove xvals/yvals/squares that are empty.


class YVals
{
private:
    std::map<int, Square> squares;
public:
    YVals() {}

    int size() { return squares.size(); }

    void apply(int x, SpatialQuery*g)
    {
        // could use std::for_each...
        auto begin = squares.lower_bound(getYCoord(g->center.y                    - g->radius));
        auto end =   squares.upper_bound(getYCoord(g->center.y + g->center.height + g->radius));
        for (auto it = begin; it != end; ++it)
        {
            int y = it->first;
            if (g->includes(x, y))
            {
                it->second.apply(x, y, g);
            }
        }
    }

    void apply(int x, SquareQuery*g)
    {
        // could use std::for_each...
        auto begin = squares.lower_bound(getYCoord(g->center.y                    - g->radius));
        auto end =   squares.upper_bound(getYCoord(g->center.y + g->center.height + g->radius));
        for (auto it = begin; it != end; ++it)
        {
            int y = it->first;
            if (g->includes(x, y))
            {
                g->apply(&(it->second));
            }
        }
    }
};

class XVals
{
private:
    std::map<int, YVals> yvals;
public:
    XVals() {}

    int size() { return yvals.size(); }

    void apply(SpatialQuery*g)
    {
        // could use std::for_each...
        auto begin = yvals.lower_bound(getYCoord(g->center.x                   - g->radius));
        auto end =   yvals.upper_bound(getYCoord(g->center.x + g->center.width + g->radius));
        for (auto it = begin; it != end; ++it)
        {
            it->second.apply(it->first, g);
        }
    }

    void apply(SquareQuery*g)
    {
        // could use std::for_each...
        auto begin = yvals.lower_bound(getYCoord(g->center.x                   - g->radius));
        auto end =   yvals.upper_bound(getYCoord(g->center.x + g->center.width + g->radius));
        for (auto it = begin; it != end; ++it)
        {
            it->second.apply(it->first, g);
        }
    }
};





class AddAll : public SquareQuery
{
private:
    Spatial* sp;
public:
    AddAll(Spatial* sp_) : SquareQuery{sp_->get_area(), 0}, sp{sp_} {}
    void apply(Square*sq)
    {
        sq->add(sp);
    }
};
class RemoveAll : public SquareQuery
{
private:
    Spatial* sp;
public:
    RemoveAll(Spatial* sp_) : SquareQuery{sp_->get_area(), 0}, sp{sp_} {}
    void apply(Square*sq)
    {
        sq->remove(sp);
    }

};
class IntersectsAny : public SpatialQuery
{
private:
    bool intersected;
    Spatial* sp;
public:
    IntersectsAny(Spatial* sp_) : SpatialQuery{sp_->get_area(), 0}, intersected{false}, sp{sp_} {}

    void apply(Spatial*other)
    {
        intersected |= sp != other && sp->get_area().overlaps(other->get_area());
    }

    bool includes(int x, int y)
    {
        return !intersected && Query::includes(x, y);
    }

    bool retVal() const
    {
        return intersected;
    }
};






Grid::Grid() : xvals{new XVals()} {}
Grid::~Grid() { delete xvals; }

void Grid::remove(Spatial* a) { RemoveAll q{a}; apply(&q); }
void Grid::add(Spatial* a)    {    AddAll q{a}; apply(&q); }

bool Grid::overlaps(Spatial* sp) { IntersectsAny q{sp}; apply(&q); return q.retVal(); }

void Grid::apply(SpatialQuery*q) { xvals->apply(q); }
void Grid::apply(SquareQuery*q)  { xvals->apply(q); }


}


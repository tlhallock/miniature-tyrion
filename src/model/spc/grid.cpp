
#include "model/spc/grid.h"

#include "model/spc/grid_internals.h"

#include <vector>
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

    friend std::ostream& operator<<(std::ostream& out, const YVals& y)
    {
        for (auto it = y.squares.begin(); it != y.squares.end(); ++it)
        {
            out << "{" << it->first << ": " << it->second << "} ";
        }
        return out;
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
        int xmin = getYCoord(g->center.x                   - g->radius);
        int xmax = getYCoord(g->center.x + g->center.width + g->radius);

        if (g->createOnEmpty())
        {
            for (int x = xmin; x < xmax; x++)
            {
                auto it = yvals.find(x);
                if (it == yvals.end())
                {
                    yvals.insert(std::pair<int, YVals>{x, YVals{}});
                }

                it = yvals.find(x);
                it->second.apply(it->first, g);
            }
        }
        else
        {
            // could use std::for_each...
            auto begin = yvals.lower_bound(xmin);
            auto end =   yvals.upper_bound(xmax);
            for (auto it = begin; it != end; ++it)
            {
                it->second.apply(it->first, g);
            }
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


    friend std::ostream& operator<<(std::ostream& out, const XVals& x)
    {
        for (auto it = x.yvals.begin(); it != x.yvals.end(); ++it)
        {
            out << "\t" << it->first << ": " << it->second << '\n';
        }
        return out;
    }
};





class AddAll : public SquareQuery
{
private:
    Spatial* sp;
public:
    AddAll(Spatial* sp_) : SquareQuery{sp_->getArea(), 0}, sp{sp_} {}
    void apply(Square*sq)
    {
        sq->add(sp);
    }
    bool createOnEmpty() { return true; }
};
class RemoveAll : public SquareQuery
{
private:
    Spatial* sp;
public:
    RemoveAll(Spatial* sp_) : SquareQuery{sp_->getArea(), 0}, sp{sp_} {}
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
    IntersectsAny(Spatial* sp_) : SpatialQuery{sp_->getArea(), 0}, intersected{false}, sp{sp_} {}

    void apply(Spatial*other)
    {
        intersected |= sp != other && sp->getArea().overlaps(other->getArea());
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


std::ostream& operator<<(std::ostream& out, const Grid& g)
{
    return out << *g.xvals << std::endl;
}





#define SIZE 1000.0
#define NPOINTS 5

class Test : public Spatial
{
public:
    Area area;
    Test() : area{SIZE * rand() / (double) RAND_MAX, SIZE * rand() / (double) RAND_MAX, .5, .5} {}
    const Area& getArea() { return area; }
};



void test()
{
    Grid g;

    std::vector<Test> t;
    t.resize(NPOINTS);

    for (int i=0;i<NPOINTS;i++)
    {
        g.add(&t[i]);
    }

    std::cout << g << std::endl;

}








}


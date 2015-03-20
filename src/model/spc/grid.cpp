
#include "model/spc/grid.h"
#include "model/spc/area_spatial.h"

#include "model/spc/grid_internals.h"

#include <vector>
#include <map>

namespace aoe
{

// TODO: Remove xvals/yvals/squares that are empty.



#define VERBOSE 0

class YVals
{
private:
    std::map<int, Square> squares;
public:
    YVals() {}

    int size() { return squares.size(); }

    void apply(int x, SpatialQuery*g)
    {
        int ymin = getYCoord(g->center.y                    - g->radius);
        int ymax = getYCoord(g->center.y + g->center.height + g->radius) + 1;

        if (g->createOnEmpty())
        {
            for (int y = ymin; y < ymax; y++)
            {
                auto it = squares.find(y);
                if (it == squares.end())
                {
                    squares.insert(std::pair<int, Square>{y, Square{}});
                    it = squares.find(y);
                }

                if (g->includes(x, y))
                {
                    it->second.apply(x, y, g);
                }
            }
        }
        else
        {
            auto begin = squares.lower_bound(ymin);
            auto end =   squares.upper_bound(ymax);
            for (auto it = begin; it != end; ++it)
            {
                int y = it->first;
                if (g->includes(x, y))
                {
                    it->second.apply(x, y, g);
                }
            }
        }
    }

    void apply(int x, SquareQuery*g)
    {
        int ymin = getYCoord(g->center.y                    - g->radius);
        int ymax = getYCoord(g->center.y + g->center.height + g->radius) + 1;

#if VERBOSE
        std::cout << '\t' << g->center.y << ", " << g->center.height << ", " << g->radius << std::endl;
        std::cout << "\tinside yvals " << ymin << ", " << ymax << std::endl;
#endif

        if (g->createOnEmpty())
        {
            for (int y = ymin; y < ymax; y++)
            {
                auto it = squares.find(y);
                if (it == squares.end())
                {
                    squares.insert(std::pair<int, Square>{y, Square{}});
                    it = squares.find(y);
                }

                std::cout << "Checking if " << g->center << " + " << g->radius << " includes " << x << ", " << y << std::endl;
                if (g->includes(x, y))
                {
                    g->apply(&(it->second));
                    std::cout << "yes" << std::endl;
                }
                std::cout << "no" << std::endl;

                std::string input;
                std::cin >> input;
            }
        }
        else
        {
            // could use std::for_each...
            auto begin = squares.lower_bound(ymin);
            auto end =   squares.upper_bound(ymax);
            for (auto it = begin; it != end; ++it)
            {
                int y = it->first;
                if (g->includes(x, y))
                {
                    g->apply(&(it->second));
                }
            }
        }
    }

    void collapseUnusedSquares()
    {
        auto end = squares.end();
        for (auto it = squares.begin(); it != end;)
        {
            if (it->second.size() == 0)
            {
                squares.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }

    int count() const
    {
        int count = 0;
        auto end = squares.end();
        for (auto it = squares.begin(); it != end; ++it)
        {
            count += it->second.size();
        }
        return count;
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

    template<class Q> void apply(Q*g)
    {
        int xmin = getYCoord(g->center.x                   - g->radius);
        int xmax = getYCoord(g->center.x + g->center.width + g->radius) + 1;

#if VERBOSE
        std::cout << g->center.x << ", " << g->center.width << ", " << g->radius << std::endl;
        std::cout << "inside xvals " << xmin << ", " << xmax << std::endl;
#endif


        if (g->createOnEmpty())
        {
            for (int x = xmin; x < xmax; x++)
            {
                auto it = yvals.find(x);
                if (it == yvals.end())
                {
                    yvals.insert(std::pair<int, YVals>{x, YVals{}});
                    it = yvals.find(x);
                }

                it->second.apply(it->first, g);
            }
        }
        else
        {
            auto begin = yvals.lower_bound(xmin);
            auto end =   yvals.upper_bound(xmax);
            for (auto it = begin; it != end; ++it)
            {
                it->second.apply(it->first, g);
            }
        }
    }

    void collapseUnusedSquares()
    {
        auto end = yvals.end();
        for (auto it = yvals.begin(); it != end;)
        {
            it->second.collapseUnusedSquares();
            if (it->second.size() == 0)
            {
                yvals.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }

    int count() const
    {
        int count = 0;
        auto end = yvals.end();
        for (auto it = yvals.begin(); it != end; ++it)
        {
            count += it->second.count();
        }
        return count;
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
    bool createOnEmpty() const { return true; }
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

class PrintRange : public SpatialQuery
{
    PrintRange(Spatial* sp_, double r) : SpatialQuery{sp_->getArea(), r} {}

    void apply(Spatial* other)
    {
        std::cout << "In range of " << other->getArea() << std::endl;
    }
};




Grid::Grid() : xvals{new XVals()} {}
Grid::~Grid() { delete xvals; }

void Grid::remove(Spatial* a) { RemoveAll q{a}; apply(&q); }
void Grid::add(Spatial* a)    {    AddAll q{a}; apply(&q); }

bool Grid::overlaps(Spatial* sp) { IntersectsAny q{sp}; apply(&q); return q.retVal(); }

void Grid::apply(SpatialQuery*q) { xvals->apply(q); }
void Grid::apply(SquareQuery*q)  { xvals->apply(q); }

void Grid::collapseUnusedSquares()
{
    xvals->collapseUnusedSquares();
}


int Grid::count() const
{
    return xvals->count();
}


std::ostream& operator<<(std::ostream& out, const Grid& g)
{
    return out << *g.xvals << std::endl;
}





#define SIZE 1000.0
#define NPOINTS 50

class Test : public SimpleSpatial
{
public:
    Area area;
    Test() : SimpleSpatial{Area{SIZE * (rand() / (double) RAND_MAX),
                  SIZE * (rand() / (double) RAND_MAX),
                  .5, .5}} {}
    Area& getArea() { return area; }
};



void test()
{
    Grid g;

    std::vector<Test> t;
    t.resize(NPOINTS);
    bool in[NPOINTS];

    for (int i=0;i<NPOINTS;i++)
    {
        in[i] = false;
    }

    for (int i=0;i<10;i++)
    {
        int idx = rand() % NPOINTS;
        if (in[idx])
        {
            g.remove(&t[idx]);
            in[idx] = false;
        }
        else
        {
            g.add(&t[idx]);
            in[idx] = true;
        }
        std::cout << g << std::endl;
    }

//    for (int i=0;i<NPOINTS;i++)
//    {
//        g.add(&t[i]);
//        in[i] = true;
//    }

    std::cout << g.count() << std::endl;

    g.collapseUnusedSquares();

    std::cout << g << std::endl;
}








}


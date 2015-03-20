
#include "model/spc/area.h"

#include <cmath>

namespace aoe
{


Area::Area() :
    Location{0, 0},
    Size{0, 0} {}

Area::Area(double mx, double my, double mw, double mh) :
   Location{mx, my},
   Size{mw, mh} {}

bool Area::contains(const Area& other) const
{
    std::cout << "Fix method area::contains" << std::endl;
  return 
    x < other.x && y < other.y &&
       x + width > other.x && y + height > other.y;
}


std::ostream& operator<<(std::ostream& out, const Area& a)
{
  return out << "[(" << a.x << "," << a.y <<")-(" << (a.x + a.width) << "," << (a.y + a.height) << ")]";
}


bool Area::overlaps(const Area& r) const
{
    double tw = this->width;
    double th = this->height;
    double rw = r.width;
    double rh = r.height;
    if (rw < 0 || rh < 0 || tw < 0 || th < 0)
    {
        return false;
    }
    double tx = this->x;
    double ty = this->y;
    double rx = r.x;
    double ry = r.y;
    rw += rx;
    rh += ry;
    tw += tx;
    th += ty;

    return ((rw < rx || rw > tx) &&
            (rh < ry || rh > ty) &&
            (tw < tx || tw > rx) &&
            (th < ty || th > ry));
}


Area& Area::operator=(const Location& loc)
{
    x = loc.x;
    y = loc.y;
    return *this;
}

Area& Area::operator=(const Size& size)
{
    width = size.width;
    height = size.height;
    return *this;
}


double Area::distanceTo(const Location& other) const
{
    double dx = 0;
    if (other.x > x + width)
    {
        dx = other.x - (x + width);
    }
    else if (other.x < x)
    {
        dx = x - other.x;
    }
    else
    {
        dx = 0;
    }

    double dy = 0;
    if (other.y > y + height)
    {
        dy = other.y - (y + height);
    }
    else if (other.y < y)
    {
        dy = y - other.y;
    }
    else
    {
        dy = 0;
    }

    return sqrt(dx*dx+dy*dy);
}

namespace
{
    inline double min(double x, double y)
    {
        return x<y?x:y;
    }

    inline double di(double x1, double y1, double x2, double y2)
    {
        double dx = x1-x2;
        double dy = y1-y2;
        return sqrt(dx*dx+dy*dy);
    }
}


double Area::distanceTo(const Area& other) const
{
    const bool left  = other.x + other.width  <= x;
    const bool right = other.x                >= x + width;
    const bool below = other.y + other.height <= y;
    const bool above = other.y                >= y + height;

         if (left  && above) return di(x        , y + height, other.x + other.width, other.y               );
    else if (left  && below) return di(x        , y         , other.x + other.width, other.y + other.height);
    else if (right && above) return di(x + width, y + height, other.x              , other.y               );
    else if (right && below) return di(x + width, y         , other.x              , other.y + other.height);
    else if (left )          return       x - (other.x + other.width );
    else if (right)          return other.x - (      x +       width );
    else if (below)          return       y - (other.y + other.height);
    else if (above)          return other.y - (      y +       height);
    else                     return 0;
}

//  #define di(x,y) (sqrt((x)+(y)))

//      const double xw = x + width;
//      const double yh = y + height;
//      const double oxw = other.x + other.width;
//      const double oyh = other.y + other.height;

//      const double dx1 = x  - other.x;
//      const double dx2 = xw - other.x;
//      const double dx3 = x  - oxw;
//      const double dx4 = xw - oxw;

//      const double dy1 = y  - other.y;
//      const double dy2 = yh - other.y;
//      const double dy3 = y  - oyh;
//      const double dy4 = yh - oyh;

//      const double dx1sq = dx1*dx1;
//      const double dx2sq = dx2*dx2;
//      const double dx3sq = dx3*dx3;
//      const double dx4sq = dx4*dx4;

//      const double dy1sq = dy1*dy1;
//      const double dy2sq = dy2*dy2;
//      const double dy3sq = dy3*dy3;
//      const double dy4sq = dy4*dy4;

//      const double d01 = sqrt(dx1sq + dy1sq);
//      const double d02 = sqrt(dx1sq + dy2sq);
//      const double d03 = sqrt(dx1sq + dy3sq);
//      const double d04 = sqrt(dx1sq + dy4sq);
//      const double d05 = sqrt(dx2sq + dy1sq);
//      const double d06 = sqrt(dx2sq + dy2sq);
//      const double d07 = sqrt(dx2sq + dy3sq);
//      const double d08 = sqrt(dx2sq + dy4sq);
//      const double d09 = sqrt(dx3sq + dy1sq);
//      const double d10 = sqrt(dx3sq + dy2sq);
//      const double d11 = sqrt(dx3sq + dy3sq);
//      const double d12 = sqrt(dx3sq + dy4sq);
//      const double d13 = sqrt(dx4sq + dy1sq);
//      const double d14 = sqrt(dx4sq + dy2sq);
//      const double d15 = sqrt(dx4sq + dy3sq);
//      const double d16 = sqrt(dx4sq + dy4sq);

//      const double d1_1 = min(d01, d02);
//      const double d2_1 = min(d03, d04);
//      const double d3_1 = min(d05, d06);
//      const double d4_1 = min(d07, d08);
//      const double d5_1 = min(d09, d10);
//      const double d6_1 = min(d11, d12);
//      const double d7_1 = min(d13, d14);
//      const double d8_1 = min(d15, d16);

//      const double d1_2 = min(d1_1, d2_1);
//      const double d2_2 = min(d3_1, d4_1);
//      const double d3_2 = min(d5_1, d6_1);
//      const double d4_2 = min(d7_1, d8_1);

//      const double d1_3 = min(d1_2, d2_2);
//      const double d2_3 = min(d3_2, d4_2);

//      return min(d1_3, d2_3);












//inline double di(double x1, double y1, double x2, double y3)
//{
//    double dx = x1-x2;
//    double dy = y1-y2;
//    return sqrt(dx*dx+dy*dy);
//}

//    double dx01 = di(x        , y         , other.x              , other.y               );
//    double dx02 = di(x        , y         , other.x + other.width, other.y               );
//    double dx03 = di(x        , y         , other.x              , other.y + other.height);
//    double dx04 = di(x        , y         , other.x + other.width, other.y + other.height);
//    double dx05 = di(x + width, y         , other.x              , other.y               );
//    double dx06 = di(x + width, y         , other.x + other.width, other.y               );
//    double dx07 = di(x + width, y         , other.x              , other.y + other.height);
//    double dx08 = di(x + width, y         , other.x + other.width, other.y + other.height);
//    double dx09 = di(x        , y + height, other.x              , other.y               );
//    double dx10 = di(x        , y + height, other.x + other.width, other.y               );
//    double dx11 = di(x        , y + height, other.x              , other.y + other.height);
//    double dx12 = di(x        , y + height, other.x + other.width, other.y + other.height);
//    double dx13 = di(x + width, y + height, other.x              , other.y               );
//    double dx14 = di(x + width, y + height, other.x + other.width, other.y               );
//    double dx15 = di(x + width, y + height, other.x              , other.y + other.height);
//    double dx16 = di(x + width, y + height, other.x + other.width, other.y + other.height);

//    dx01 = min(dx01, dx02);
//    dx02 = min(dx03, dx04);
//    dx03 = min(dx05, dx06);
//    dx04 = min(dx07, dx08);
//    dx05 = min(dx09, dx10);
//    dx06 = min(dx11, dx12);
//    dx07 = min(dx13, dx14);
//    dx08 = min(dx15, dx16);

//    dx01 = min(dx01, dx02);
//    dx02 = min(dx03, dx04);
//    dx03 = min(dx05, dx06);
//    dx04 = min(dx07, dx08);

//    dx01 = min(dx01, dx02);
//    dx02 = min(dx03, dx04);

//    return min(dx01, dx02);




//const double xw = x + width;
//const double yh = y + height;
//const double oxw = other.x + other.width;
//const double oyh = other.y + other.height;


//double dx01 = di(x , y , other.x   , other.y);
//double dx02 = di(x , y , oxw       , other.y);
//double dx03 = di(x , y , other.x   , oyh    );
//double dx04 = di(x , y , oxw       , oyh    );
//double dx05 = di(xw, y , other.x   , other.y);
//double dx06 = di(xw, y , oxw       , other.y);
//double dx07 = di(xw, y , other.x   , oyh    );
//double dx08 = di(xw, y , oxw       , oyh    );
//double dx09 = di(x , yh, other.x   , other.y);
//double dx10 = di(x , yh, oxw       , other.y);
//double dx11 = di(x , yh, other.x   , oyh    );
//double dx12 = di(x , yh, oxw       , oyh    );
//double dx13 = di(xw, yh, other.x   , other.y);
//double dx14 = di(xw, yh, oxw       , other.y);
//double dx15 = di(xw, yh, other.x   , oyh    );
//double dx16 = di(xw, yh, oxw       , oyh    );

//dx01 = min(dx01, dx02);
//dx02 = min(dx03, dx04);
//dx03 = min(dx05, dx06);
//dx04 = min(dx07, dx08);
//dx05 = min(dx09, dx10);
//dx06 = min(dx11, dx12);
//dx07 = min(dx13, dx14);
//dx08 = min(dx15, dx16);

//dx01 = min(dx01, dx02);
//dx02 = min(dx03, dx04);
//dx03 = min(dx05, dx06);
//dx04 = min(dx07, dx08);

//dx01 = min(dx01, dx02);
//dx02 = min(dx03, dx04);

//return min(dx01, dx02);

}

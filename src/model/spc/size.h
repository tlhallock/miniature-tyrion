#ifndef SIZE_H
#define SIZE_H


#include <iostream>

namespace aoe
{


class Size
{
public:
    double width, height;

    Size();
    Size(double x, double y);

    virtual ~Size();

    Size operator/(double d) const;
    Size operator*(double d) const;

    void setWidth(double w);
    void setHeight(double h);
    void setSize(double w, double h);

    double getWidth() const;
    double getHeight() const;

    friend std::ostream& operator<<(std::ostream& out, const Size& a);
};


struct SizeCmp
{
    bool operator() (const Size& l1, const Size& l2);
};

}

#endif // SIZE_H

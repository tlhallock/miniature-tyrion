#include "model/spc/size.h"


namespace aoe
{

Size::Size() : width{0}, height{0} {}

Size::Size(double width_, double height_) : width{width_}, height{height_} {}

Size::~Size() {}

void Size::setWidth(double width_)
{
    width = width_;
}

void Size::setHeight(double height_)
{
    height = height_;
}

double Size::getWidth() const
{
    return width;
}
double Size::getHeight() const
{
    return height;
}

void Size::setSize(double width_, double height_)
{
    width = width_;
    height = height_;
}


bool SizeCmp::operator() (const Size& l1, const Size& l2)
{
    if (l1.width == l2.width)
    {
        return l1.height < l2.height;
    }
    else
    {
        return l1.width < l2.width;
    }
}

Size Size::operator*(double d) const
{
    return Size{width * d, height * d};
}

Size Size::operator/(double d) const
{
    return Size{width / d, height / d};
}

std::ostream& operator<<(std::ostream& out, const Size& a)
{
    return out << "[" << a.width << "," << a.height << "]";
}

}


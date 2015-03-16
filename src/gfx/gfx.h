#ifndef GFX_H
#define GFX_H

namespace aoe
{

class Area;

class Gfx
{
public:
    Gfx();
    ~Gfx();

    virtual int getImageId() const = 0;

    virtual const Area& getArea() const = 0;
    virtual Area& getArea() = 0;
};

}

#endif // GFX_H

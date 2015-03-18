#ifndef GFX_H
#define GFX_H

#include "model/spc/spatial.h"

namespace aoe
{

class Area;

class Gfx : public Spatial
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

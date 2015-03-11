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

    virtual int get_image_id() const = 0;
    virtual const Area& get_location() const = 0;
};

}

#endif // GFX_H

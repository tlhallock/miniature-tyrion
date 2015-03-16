#ifndef GFXOBJECT_H
#define GFXOBJECT_H

#include "opencv2/core/opengl.hpp"

#include "gfx/gfx.h"

#include "model/spc/location.h"



#define DEBUG_OPENGL 0


namespace aoe
{

class Size;
class Location;
class Unit;
class GlDrawInstanceCmp;

class GfxObject
{
    cv::ogl::Arrays arr;
    cv::ogl::Texture2D tex;
    cv::ogl::Buffer indices;

#if DEBUG_OPENGL
public:
    Location size;
private:
#endif



public:
    GfxObject(const Size& pos,
              const std::string& object_file, const cv::Mat& img);
    ~GfxObject();

    void draw();
};


class GlDrawInstance
{
    friend class GlDrawInstanceCmp;

private:
    Gfx* original;
    Location pos;
    GfxObject* type;

public:
    GlDrawInstance(Gfx* original, GfxObject* type);
    GlDrawInstance(GfxObject* type);
    ~GlDrawInstance();

    void draw();
    Gfx* getOriginal();

private:
    void updatePosition();
};

struct GlDrawInstanceCmp
{
    bool operator() (const GlDrawInstance& l1, const GlDrawInstance& l2)
    {
        if (l1.pos.x == l2.pos.x)
        {
            return l1.pos.y < l2.pos.y;
        }
        else if (l1.pos.y == l2.pos.y)
        {
            return l1.original < l2.original;
        }
        else
        {
            return l1.pos.x < l2.pos.x;
        }
    }
};

}


#endif // GFXOBJECT_H

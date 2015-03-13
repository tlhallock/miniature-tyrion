#ifndef GFXOBJECT_H
#define GFXOBJECT_H

class GfxObject
{
    cv::ogl::Arrays arr;
    cv::ogl::Texture2D tex;
    cv::ogl::Buffer indices;

public:
    GfxObject(int w, int h,
              const std::string& object, const std::string& texture_file);
    ~GfxObject();

    void draw();
};


class GlDrawInstance
{
private:
    double x, y;
    GlDrawObject type;

public:
    GlDrawObject(double w, double h, GlDrawType* type_);
    ~GlDrawObject();

    void setPosition(double x_, double y_);

    void draw();

    // To be removed...
    double get_x();
    double get_y();
};


#endif // GFXOBJECT_H

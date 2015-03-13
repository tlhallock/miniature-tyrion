#ifndef GLDISPLAY_H
#define GLDISPLAY_H

class GlDisplay : public ViewportListener
{
private:
    std::vector<GLDrawType> drawTypes;
    std::vector<GlDrawObject> drawables;

public:
    GlDisplay();
    ~GlDisplay();


public:
    static void show(Game* game, Images* images);


};

#endif // GLDISPLAY_H

#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include "gfx/gfxobject.h"
#include "gfx/viewport_listener.h"
#include "model/area.h"

#include <vector>
#include <map>
#include <thread>


namespace aoe
{


class Game;
class Images;
class GameInfo;
class GlDisplay;

void onMouse( int event, int x, int y, int state, void* ptr);
void draw_func(void* userdata);




class GlDisplay : public ViewportListener
{
    friend void onMouse( int event, int x, int y, int state, void* ptr);
    friend void draw_func(void* userdata);

private:
    std::string name;

    std::map<int, GfxObject> drawTypes;
    std::vector<GlDrawInstance> drawables;

    Area area;
    int w, h;

    double camera_x;
    double camera_y;
    double camera_z;

//    std::thread* render_thread;

public:
    GlDisplay(GameInfo& info, const std::string& name);
    virtual ~GlDisplay();

    void zoom_in();
    void zoom_out();

    void left();
    void right();
    void up();
    void down();

    void unit_entered(Unit* entered);
    void unit_exited(Unit* exit);

    void renderLoop(Game* game);

private:

    void load(GameInfo& civ);
    void draw();
    void setCamera(double x, double y, double z);
};

}


#endif // GLDISPLAY_H

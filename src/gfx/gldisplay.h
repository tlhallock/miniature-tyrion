#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include "gfx/gfxobject.h"
#include "gfx/viewport_listener.h"
#include "model/area.h"

#include <vector>
#include <map>


namespace aoe
{


class Game;
class Images;
class GameInfo;

class GlDisplay : public ViewportListener
{
private:
    std::map<int, GfxObject> drawTypes;
    std::vector<GlDrawInstance> drawables;
    Area area;

public:
    GlDisplay();
    ~GlDisplay();

    void zoom_in();
    void zoom_out();

    void left();
    void right();
    void forward();
    void backward();

    void unit_entered(Unit* entered);
    void unit_exited(Unit* exit);

    void depict(Game* game, Images* images);
    static void createDisplay(Game* game, Images* images);

    void load(GameInfo& civ);

    void draw();
};

}


#endif // GLDISPLAY_H

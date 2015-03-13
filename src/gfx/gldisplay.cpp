#include "gfx/gldisplay.h"

#include "model/game.h"
#include "res/game_info.h"
#include "model/unit.h"

#include <iostream>
#include "cvconfig.h"
#include <opencv2/highgui.hpp>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "opencv2/core/core.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "main/settings.h"

namespace aoe
{

unsigned long current_time()
{
    return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1);
}

struct last_event {
    int x, y, event;
    unsigned long time = current_time();
};

void onMouse( int event, int x, int y, int state, void* ptr)
{
    GlDisplay* display = static_cast<GlDisplay*>(ptr);
    if (state != 4)
    {
        return;
    }

    unsigned long millis = current_time();

    static last_event previous;

    if (y > previous.y)
    {
        display->zoom_out();
    }
    else
    {
        display->zoom_in();
    }

    previous.x = x;
    previous.y = y;
    previous.event = event;
    previous.time = millis;
}

void draw_func(void* userdata)
{
    (static_cast<GlDisplay*>(userdata))->draw();
}

























GlDisplay::GlDisplay(GameInfo& info, const std::string& name_) :
    ViewportListener{&area},
    name{name_},
    current_range{Settings::get_instance().INITIAL_HEIGHT}
{
    cv::namedWindow(name, cv::WINDOW_OPENGL);
    cv::resizeWindow(name,
                     Settings::get_instance().DISPLAY_WIDTH,
                     Settings::get_instance().DISPLAY_HEIGHT);

    load(info);

    cv::setOpenGlDrawCallback(name, draw_func, this);
    cv::setMouseCallback(name, onMouse, this);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, area.w / area.h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, current_range, 0, 0, 0, 0, 1, 0);
}


GlDisplay::~GlDisplay()
{
    cv::setOpenGlDrawCallback(name, 0, 0);
    cv::destroyWindow(name);
}


void GlDisplay::unit_entered(Unit* entered)
{
    int id = entered->get_type()->get_id();
    auto it = drawTypes.find(id);
    if (it == drawTypes.end())
    {
        std::cerr << "Unkown unit: " << id << std::endl;
        exit(-1);
    }

    drawables.push_back(GlDrawInstance{entered, &it->second});
}

void GlDisplay::unit_exited(Unit* exit)
{
    // Could me more efficient...
    for (auto it = drawables.begin(); it != drawables.end(); ++it)
    {
        if (it->getOriginal() == exit)
        {
            drawables.erase(it);
            return;
        }
    }
}


void GlDisplay::load(GameInfo& info)
{
    for (auto it = info.get_units().begin(); it != info.get_units().end(); ++it)
    {
        if (!it->isCreatable())
        {
            continue;
        }

        // The image needs to actually be dynamic...
        drawTypes.insert(std::pair<int, GfxObject>{
                             it->get_id(),
                             GfxObject{it->get_width(),
                                       it->get_height(),
                                       "not used",
                                       info.get_images()->get(it->get_image_id())}});
    }
}

void GlDisplay::draw()
{
//    GlDrawObject* moving = drawables[0];
//    moving->setPosition(moving->get_x() + .001, moving->get_y());

    for (int i=0;i<drawables.size();i++)
    {
        drawables[i].draw();
    }
}

void GlDisplay::renderLoop(Game* game)
{
    game->get_map().add_listener(this);
    for (;;)
    {
        cv::updateWindow(name);
        int key = cv::waitKey(1000);
        if ((key & 0xff) == 27)
            break;
    }
    game->get_map().remove_listener(this);
}








void GlDisplay::zoom_in()
{
    std::cout << "in" << std::endl;

    //gluLookAt(0, 0, current_range, 0, 0, 0, 0, 1, 0);
}

void GlDisplay::zoom_out()
{
    std::cout << "out" << std::endl;

    //gluLookAt(0, 0, current_range, 0, 0, 0, 0, 1, 0);
}


void GlDisplay::left()
{
    std::cout << "left" << std::endl;
}

void GlDisplay::right()
{
    std::cout << "right" << std::endl;
}

void GlDisplay::forward()
{
    std::cout << "forward" << std::endl;
}

void GlDisplay::backward()
{
    std::cout << "back" << std::endl;
}










}

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
    w {Settings::get_instance().DISPLAY_WIDTH},
    h {Settings::get_instance().DISPLAY_HEIGHT},
    camera_x{0},
    camera_y{0},
    camera_z{Settings::get_instance().INITIAL_HEIGHT}
{
    cv::namedWindow(name, cv::WINDOW_OPENGL | cv::WINDOW_NORMAL);
    cv::resizeWindow(name, w, h);

    load(info);

    std::cout << "The area is " << area << std::endl;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, w / (double) h, 0.1, 100.0);

    map = std::unique_ptr<GfxObject>{new GfxObject{
            Size{Settings::get_instance().MAP_WIDTH, Settings::get_instance().MAP_HEIGHT},
            "not used", info.get_images()->get_background()}};
    mapInstance = std::unique_ptr<GlDrawInstance>{new GlDrawInstance{map.get()}};

    cv::setOpenGlDrawCallback(name, draw_func, this);
    cv::setMouseCallback(name, onMouse, this);
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
        std::cerr << "Unkown unit id: " << id << std::endl;
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

void GlDisplay::handle_key(int key)
{
    std::cout << key << std::endl;

    switch (key)
    {
    case 97: // left
        left(); return;
    case 115: // down
        down(); return;
    case 100: // right
        right(); return;
    case 119: // up
        up(); return;


    default:
        return;
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

//        int image_id = info.get_images()->get_id_for()

        // The image needs to actually be dynamic...
        drawTypes.insert(std::pair<int, GfxObject>{
                             it->get_id(),
                             GfxObject{
                                       it->getSize(),
                                       "not used",
                                       info.get_images()->get(it->get_image_id())}});
    }
}

void GlDisplay::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    gluLookAt(camera_x, camera_y, camera_z, 0, 0, 0, 0, 1, 0);
    gluLookAt(0, 0, camera_z, 0, 0, 0, 0, 1, 0);
    glTranslated(camera_x, camera_y, 0);

    if (mapInstance)
    {
        mapInstance->draw();
    }

    for (int i=0;i<(int)drawables.size();i++)
    {
        drawables[i].draw();
    }
}

void GlDisplay::renderLoop(Game* game)
{
    game->get_map().add_listener(this);
    for (;;)
    {
        std::cout << camera_z << std::endl;
        cv::updateWindow(name);
        int key = cv::waitKey(Settings::get_instance().KEY_WAIT_TIME);
        if ((key & 0xff) == 27)
            break;
        if (key < 0)
        {
            continue;
        }

        handle_key(key);
    }
    game->get_map().remove_listener(this);
}


void GlDisplay::setCamera(double x, double y, double z)
{
    camera_x = x;
    camera_y = y;
    camera_z = z;
}

void GlDisplay::zoom_in()
{
    double amount = Settings::get_instance().ZOOM_AMOUNT;
    if (amount > (camera_z - .1) / 2)
    {
        amount = (camera_z - .1) / 2;
    }
    camera_z -= amount;
    if (camera_z < 0)
    {
        camera_z = 0;
    }
}

void GlDisplay::zoom_out()
{
    double amount = Settings::get_instance().ZOOM_AMOUNT;
    camera_z += amount;
}


void GlDisplay::left()
{
    camera_x += Settings::get_instance().ZOOM_AMOUNT;
}

void GlDisplay::right()
{
    camera_x -= Settings::get_instance().ZOOM_AMOUNT;
}

void GlDisplay::up()
{
    camera_y -= Settings::get_instance().ZOOM_AMOUNT;
}

void GlDisplay::down()
{
    camera_y += Settings::get_instance().ZOOM_AMOUNT;
}










}

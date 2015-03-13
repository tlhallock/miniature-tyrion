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


GlDisplay::GlDisplay() :
    ViewportListener{&area}
{
    cv::namedWindow("OpenGL", cv::WINDOW_OPENGL);
    cv::resizeWindow("OpenGL",
                     Settings::get_instance().DISPLAY_WIDTH,
                     Settings::get_instance().DISPLAY_HEIGHT);
}


GlDisplay::~GlDisplay()
{
    cv::setOpenGlDrawCallback("OpenGL", 0, 0);
    cv::destroyWindow("OpenGL");
}


void GlDisplay::depict(Game* game, Images* images)
{
    game->get_map().add_listener(this);
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

extern "C"
{


void mouseMotion(int x, int y)
{
    std::cout << "called" << std::endl;
}


void mouseEvent(int button, int state, int x, int y)
{
    std::cout << "called" << std::endl;
    // Wheel reports as button 3(scroll up) and button 4(scroll down)
    if ((button == 3) || (button == 4)) // It's a wheel event
    {
        // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
        if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
        printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
    } else {  // normal button event
        printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
    }
}

void draw_func(void* userdata)
{
    (static_cast<GlDisplay*>(userdata))->draw();
}


}
































void GlDisplay::createDisplay(Game* game, Images* images)
{
    GlDisplay glDisplay;
    glDisplay.depict(game, images);


    glutMouseFunc(mouseEvent);
    glutMotionFunc(mouseMotion);

//    glDisplay.drawables.push_back(new GlDrawObject{1, 1, img});
//    glDisplay.drawables.push_back(new GlDrawObject{1, 1, img});

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, glDisplay.area.w / glDisplay.area.h, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

    cv::setOpenGlDrawCallback("OpenGL", draw_func, &glDisplay);

    for (;;)
    {
        cv::updateWindow("OpenGL");
        int key = cv::waitKey(1);
        if ((key & 0xff) == 27)
            break;
    }

    game->get_map().remove_listener(&glDisplay);
}








}

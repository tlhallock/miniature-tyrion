#include "gldisplay.h"


namespace aoe
{


GlDisplay::GlDisplay()
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

void GlDisplay::draw()
{
//    GlDrawObject* moving = drawables[0];
//    moving->setPosition(moving->get_x() + .001, moving->get_y());

    for (int i=0;i<data->drawables.size();i++)
    {
        drawables[i]->draw();
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

void draw(void* userdata)
{
    (static_cast<GlDisplay*>(userdata))->draw();
}

}

































void GlDisplay::show(Game* game, Images* images)
{
    GlDisplay glDisplay{game, images};

    glutMouseFunc(mouseEvent);
    glutMotionFunc(mouseMotion);

    data.drawables.push_back(new GlDrawObject{1, 1, img});
    data.drawables.push_back(new GlDrawObject{1, 1, img});

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double) win_width / win_height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

    cv::setOpenGlDrawCallback("OpenGL", draw, &glDisplay);

    for (;;)
    {
        cv::updateWindow("OpenGL");
        int key = cv::waitKey(1);
        if ((key & 0xff) == 27)
            break;
    }
}





}



#include <iostream>
#include "cvconfig.h"
#include <opencv2/highgui.hpp>
#include <GL/glut.h>


#ifndef HAVE_OPENGL
#error NEED OPENGL SUPPORT IN OPEN CV
#endif

extern "C"
{

#include <GL/gl.h>
#include <GL/glu.h>

}

#include "opencv2/core/core.hpp"
#include "opencv2/core/opengl.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv::cuda;


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
}



const int win_width = 800;
const int win_height = 640;

class TexCache
{
    TexCache() {}
};




class GlDrawObject
{
private:
    double x, y;

    cv::ogl::Arrays arr;
    cv::ogl::Texture2D tex;
    cv::ogl::Buffer indices;

public:
    GlDrawObject(double w, double h, cv::Mat& img) :
        x{0},
        y{0}
    {
        cv::Mat_<cv::Vec2f> vertex(1, 4);
        vertex << cv::Vec2f(0, h), cv::Vec2f(0, 0), cv::Vec2f(w, 0), cv::Vec2f(w, h);

        cv::Mat_<cv::Vec2f> texCoords(1, 4);
        texCoords << cv::Vec2f(0, 0), cv::Vec2f(0, 1), cv::Vec2f(1, 1), cv::Vec2f(1, 0);

        cv::Mat_<int> indicesm(1, 6);
        indicesm << 0, 1, 2, 2, 3, 0;

        arr.setVertexArray(vertex);
        arr.setTexCoordArray(texCoords);
        indices.copyFrom(indicesm);
        tex.copyFrom(img);
    }

    void setPosition(double x_, double y_)
    {
        x = x_; y = y_;
    }

    double get_x()
    {
        return x;
    }
    double get_y()
    {
        return y;
    }

    void draw()
    {
        glEnable(GL_TEXTURE_2D);
        tex.bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glDisable(GL_CULL_FACE);

//        std::cout << offset << std::endl;
        glTranslated(x, y, 0);

        cv::ogl::render(arr, indices, cv::ogl::TRIANGLES);

        glTranslated(-x, -y, 0);
    }
};

class DrawData
{
public:
    std::vector<GlDrawObject*> drawables;

    DrawData() {}
};


void draw(void* userdata)
{
    DrawData* data = static_cast<DrawData*>(userdata);

    GlDrawObject* moving = data->drawables[0];
    moving->setPosition(moving->get_x() + .001, moving->get_y());

    for (int i=0;i<data->drawables.size();i++)
    {
        data->drawables[i]->draw();
    }
}



int main_2(int argc, char* argv[])
{
    glutInit(&argc, argv);

    std::string filename;
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " image" << std::endl;
        filename = "../data/lena.jpg";
    }
    else
    {
        filename = argv[1];
    }




    cv::Mat img = cv::imread(filename);
    if (img.empty())
    {
        std::cerr << "Can't open image " << filename << std::endl;
        return -1;
    }
    cv::namedWindow("OpenGL", cv::WINDOW_OPENGL);
    cv::resizeWindow("OpenGL", win_width, win_height);

    glutMouseFunc(mouseEvent);
    glutMotionFunc(mouseMotion);

    DrawData data;

    data.drawables.push_back(new GlDrawObject{1, 1, img});
    data.drawables.push_back(new GlDrawObject{1, 1, img});

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double) win_width / win_height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

    cv::setOpenGlDrawCallback("OpenGL", draw, &data);

    for (;;)
    {
        cv::updateWindow("OpenGL");
        int key = cv::waitKey(1);
        if ((key & 0xff) == 27)
            break;
    }

    cv::setOpenGlDrawCallback("OpenGL", 0, 0);
    cv::destroyAllWindows();


    return 0;
}


/*
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN 1
#define NOMINMAX 1
#include <windows.h>
#endif
#if defined(_WIN64)
#include <windows.h>
#endif
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else*/



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

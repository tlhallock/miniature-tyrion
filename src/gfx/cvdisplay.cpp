
#include "gfx/cvdisplay.h"

#include <opencv2/highgui/highgui.hpp>


#include <iostream>

#define DISPLAY_WIDTH  500
#define DISPLAY_HEIGHT 500

CvDisplay::CvDisplay(Engine* engine) :
  Display{engine},
  w{DISPLAY_WIDTH},
  h{DISPLAY_HEIGHT},
  image{w, h, CV_8UC1}
{
  cv::namedWindow("Display", cv::WINDOW_AUTOSIZE);
}

CvDisplay::~CvDisplay()
{
  cv::destroyWindow("Display");
}


void CvDisplay::run()
{
  image = 0.0;
  cv::imshow("Display", image);

  std::cout << "Should be displayed now...\n";

}


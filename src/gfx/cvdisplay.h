
#ifndef CV_DISPLAY_H_
#define CV_DISPLAY_H_

#include "opencv2/core/core.hpp"

#include "gfx/display.h"
#include "model/area.h"

class CvDisplay : public Display
{
 private:
  int w, h;
  cv::Mat image;
  Area viewport;

 public:
 CvDisplay(Engine* engine);
  ~CvDisplay();

  void run();
};



#endif

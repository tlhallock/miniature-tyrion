
#ifndef CV_DISPLAY_H_
#define CV_DISPLAY_H_

#include "opencv2/core/core.hpp"

#include "gfx/display.h"
#include "model/area.h"

class Images;
class Gfx;

class CvDisplay : public Display
{
private:
    int w, h;
    cv::Mat image;
    Area viewport;
    Images* images;
public:
    CvDisplay(Game* game, Images* images);
    ~CvDisplay();

    void run();

private:
    void draw_gfx(Gfx* gfx);
};



#endif

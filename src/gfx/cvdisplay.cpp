
#include "gfx/cvdisplay.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "model/game.h"
#include "res/images.h"
#include "gfx/gfx.h"

#include "main/settings.h"


#include <iostream>

namespace aoe
{

CvDisplay::CvDisplay(Game* game, Images* images_) :
    Display{game},
    w{Settings::get_instance().DISPLAY_WIDTH},
    h{Settings::get_instance().DISPLAY_HEIGHT},
    image{w, h, CV_8UC1},
    images{images_}
{
    cv::namedWindow("Display", cv::WINDOW_AUTOSIZE);
}

CvDisplay::~CvDisplay()
{
    cv::destroyWindow("Display");
}


void CvDisplay::run()
{
    image = Settings::get_instance().BACKGROUND_COLOR;
    cv::imshow("Display", image);

    const Map& map = game->get_map();

    {
        auto end = map.get_resources().end();
        for (auto it = map.get_resources().begin(); it != end; ++it)
        {
            Resource* ptr = it->get();
            draw_gfx(ptr);
        }
    }
    {
        auto end = map.get_units().end();
        for (auto it = map.get_units().begin(); it != end; ++it)
        {
            Unit* ptr = it->get();
            draw_gfx(ptr);
        }
    }


    std::cout << "Should be displayed now...\n";
}


void CvDisplay::draw_gfx(Gfx* gfx)
{
    const Area& sub_area = gfx->get_location();
    if (!viewport.contains(sub_area))
    {
        return;
    }

    double scale_x = sub_area.x * image.cols / viewport.x;
    double scale_y = sub_area.y * image.rows / viewport.y;

    int xpx = (int) ((sub_area.x - viewport.x) * scale_x);
    int ypx = (int) ((sub_area.y - viewport.y) * scale_y);
    int wpx = (int) (sub_area.w * scale_x);
    int hpx = (int) (sub_area.h * scale_y);

    cv::Size scaledSize {wpx, hpx};

    const cv::Mat& sub_image = images->get(gfx->get_image_id());
    cv::Mat scaled;

    cv::resize(sub_image, scaled, scaledSize);

    sub_image.copyTo(image(cv::Rect(cv::Point(xpx, ypx), scaledSize)));
}


}

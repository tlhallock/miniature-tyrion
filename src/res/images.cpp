
#include "res/images.h"

#include <opencv2/highgui/highgui.hpp>

namespace aoe
{

Images::Images(const std::string& base_directory_) :
    base_directory{base_directory_},
    default_image{cv::imread(base_directory + "default.jpg")} {}

Images::~Images() {}

void Images::set(int image_id, const std::string& filename)
{
    originals.at(image_id) = cv::imread(base_directory + filename);
    if (!originals.at(image_id).data)
    {
        originals.at(image_id) = default_image;
    }
}

const cv::Mat& Images::get(int image_id) const
{
    if (image_id >= originals.size() || image_id < 0)
    {
        return default_image;
    }
    return originals.at(image_id);
}

}

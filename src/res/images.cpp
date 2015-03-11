
#include "res/images.h"

#include <opencv2/highgui/highgui.hpp>

Images::Images(const std::string& base_directory_) : base_directory{base_directory_} {}

Images::~Images() {}

void Images::set(int image_id, const std::string& filename)
{
    originals.at(image_id) = cv::imread(base_directory + filename);
}

const cv::Mat& Images::get(int image_id) const
{
    return originals.at(image_id);
}

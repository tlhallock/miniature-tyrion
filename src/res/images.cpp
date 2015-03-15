
#include "res/images.h"

#include <opencv2/highgui/highgui.hpp>

#include "main/settings.h"

#include "util/fs.h"

namespace aoe
{

Images::Images(const std::string& base_directory_) :
    base_directory{base_directory_},
    default_image{cv::imread(base_directory + "default.jpg")} {}

Images::~Images() {}


int Images::get_id_for(const std::string& filename, bool relative)
{
    std::string rp;
    if (relative)
    {
        rp = realpath(base_directory + "/" + filename);
    }
    else
    {
        rp = realpath(filename);
    }

    auto it = path_to_image.find(rp);
    if (it != path_to_image.end())
    {
        return it->second;
    }

    int id = originals.size();
    originals.push_back(cv::imread(rp));

    if (!originals[id].data)
    {
        std::cerr << "Unable to read image at " << filename << std::endl;
        exit(-1);
    }

    path_to_image.insert(std::pair<std::string, int>{rp, id});

    return id;
}

const cv::Mat& Images::get(int image_id) const
{
    if (image_id >= originals.size() || image_id < 0)
    {
        return default_image;
    }
    return originals.at(image_id);
}

cv::Mat Images::get_background()
{
    return get(get_id_for(Settings::get_instance().MAP_BACKGROUND));
}

}

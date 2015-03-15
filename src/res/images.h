
#ifndef IMAGES_H_
#define IMAGES_H_

#include <vector>
#include <map>

#include "opencv2/core/core.hpp"

namespace aoe
{

class Images
{
  std::vector<cv::Mat> originals;
  std::string base_directory;
  std::map<std::string, int> path_to_image;

  cv::Mat default_image;
 public:
  Images(const std::string& base_directory);
  ~Images();

  int get_id_for(const std::string& filename, bool relative=true);
  const cv::Mat& get(int image_id) const;

  cv::Mat get_background();
};

}

#endif


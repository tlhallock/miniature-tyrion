
#ifndef IMAGES_H_
#define IMAGES_H_

#include <vector>

#include "opencv2/core/core.hpp"

namespace aoe
{

class Images
{
  std::vector<cv::Mat> originals;
  std::string base_directory;

  cv::Mat default_image;
 public:
  Images(const std::string& base_directory);
  ~Images();

  void set(int image_id, const std::string& filename);
  const cv::Mat& get(int image_id) const;
};

}

#endif


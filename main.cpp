#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "wagon.h"

cv::Mat AddMats(const cv::Mat first, const cv::Mat second, double alpha) {
  cv::Mat fisrt_ = first.clone();
  cv::Mat sec_ = second.clone();

  if(!(alpha >= 0 && alpha <= 1)) { return fisrt_; }

  cv::resize(second, sec_, cv::Size(fisrt_.cols, fisrt_.rows));

  for (int i = 0; i < fisrt_.cols; ++i) {
    for (int j = 0; j < fisrt_.rows; ++j) {
      auto& pixel_1 = fisrt_.at<cv::Vec3b>(j, i);
      auto& pixel_2 = sec_.at<cv::Vec3b>(j, i);
      for(int c = 0; c < 3; ++c) {
        pixel_1[c] = alpha*pixel_1[c] + (1 - alpha)*pixel_2[c];
      }
    }
  }

  return fisrt_;
}

int main() {
  cv::Mat background = AddMats(cv::imread("../files/moleworm.jpg"), cv::imread("../files/google.png"), 0.6);
  Wagon wagon(background, 30, 40);
  wagon.drive_1();
  wagon.drive_2();
}
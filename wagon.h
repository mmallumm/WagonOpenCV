#include <opencv2/opencv.hpp>
#include <vector>

class Wagon {
 public:
  Wagon(cv::Mat background, double first_side = 40, double second_side = 30);
  void drive_1();
  void drive_2();
  void draw_wagon(cv::Mat background);
  void draw_full_trajectory(cv::Mat background);
  void set_position(int x, int y, double arg);

 private:
  struct TrajectoryNode {
    cv::Point2d point;
    double angle;
  };

  const double a_side_;
  const double b_side_;

  const cv::Mat background_;

  int x_ = 0;
  int y_ = 0;
  double angle_ = 0;

  std::vector<TrajectoryNode> trajectory_;
};
#include "wagon.h"

#include <cmath>

#define PI 3.14159265

double radian(double deg) { return (deg * PI / 180.0); }

double degree(double rad) { return (rad * 180.0 / PI); }

Wagon::Wagon(cv::Mat background, double first_side, double second_side)
    : background_(background), a_side_(first_side), b_side_(second_side) {
  int point_number = 500;

  double trajectory_width = background_.cols - background_.cols / 10.0;
  double trajectory_period = trajectory_width / 5.0 / (2 * PI);
  double trajectory_step = trajectory_width / point_number;
  double trajectory_begin = background_.cols / 20.0;
  double trajectory_amplitude = background_.rows / 4;

  for (int i = 0; i < point_number; ++i) {
    TrajectoryNode node;
    node.point.x = trajectory_begin + trajectory_step * i;
    node.point.y =
        trajectory_amplitude * sin(trajectory_step * i / trajectory_period) +
        background.rows / 2;
    node.angle = 0;
    trajectory_.push_back(node);
  }

  for (int i = 0; i < point_number - 1; ++i) {
    double vector_x = trajectory_[i + 1].point.x - trajectory_[i].point.x;
    double vector_y = trajectory_[i + 1].point.y - trajectory_[i].point.y;
    double cos_alpha =
        vector_x / sqrt(vector_x * vector_x + vector_y * vector_y);
    trajectory_[i].angle =
        (vector_y >= 0) ? degree(acos(cos_alpha)) : -degree(acos(cos_alpha));
  }
}

void Wagon::drive_1() {
  cv::Mat background = background_.clone();
  draw_full_trajectory(background);
  for (int i = 0; i < trajectory_.size(); ++i) {
    cv::Mat current_background = background.clone();
    set_position(trajectory_[i].point.x, trajectory_[i].point.y,
                 trajectory_[i].angle);
    draw_wagon(current_background);
    if (i == trajectory_.size() / 2) {
      cv::imwrite("../files/save_1.jpg", current_background);
    }
    cv::imshow("lab1", current_background);
    cv::waitKey(25);
  }
}

void Wagon::drive_2() {
  cv::Scalar violet(70, 30, 140);
  cv::Mat background = background_.clone();
  for (int i = 0; i < trajectory_.size(); ++i) {
    cv::Mat current_background = background.clone();
    set_position(trajectory_[i].point.x, trajectory_[i].point.y,
                 trajectory_[i].angle);
    draw_wagon(current_background);
    if (i != 0) {
      cv::line(background, trajectory_[i - 1].point, trajectory_[i].point,
               violet, 5);
    }
    if (i == trajectory_.size() / 2) {
      cv::imwrite("../files/save_2.jpg", current_background);
    }
    cv::imshow("lab1", current_background);
    cv::waitKey(25);
  }
}

void Wagon::draw_wagon(cv::Mat background) {
  double half_a = a_side_ / 2;
  double half_b = b_side_ / 2;
  cv::Point2d p0(
      -half_a * cos(radian(angle_)) - -half_b * sin(radian(angle_)) + x_,
      -half_a * sin(radian(angle_)) + -half_b * cos(radian(angle_)) + y_);
  cv::Point2d p1(
      half_a * cos(radian(angle_)) - -half_b * sin(radian(angle_)) + x_,
      half_a * sin(radian(angle_)) + -half_b * cos(radian(angle_)) + y_);
  cv::Point2d p2(
      half_a * cos(radian(angle_)) - half_b * sin(radian(angle_)) + x_,
      half_a * sin(radian(angle_)) + half_b * cos(radian(angle_)) + y_);
  cv::Point2d p3(
      -half_a * cos(radian(angle_)) - half_b * sin(radian(angle_)) + x_,
      -half_a * sin(radian(angle_)) + half_b * cos(radian(angle_)) + y_);
  cv::Scalar red(0, 0, 255);
  cv::Scalar green(0, 255, 0);
  cv::line(background, p0, p1, red, 5);
  cv::line(background, p1, p2, green, 5);
  cv::line(background, p2, p3, red, 5);
  cv::line(background, p3, p0, red, 5);
}

void Wagon::draw_full_trajectory(cv::Mat background) {
  cv::Scalar violet(70, 30, 140);
  for (int i = 0; i < trajectory_.size() - 1; ++i) {
    cv::line(background, trajectory_[i].point, trajectory_[i + 1].point, violet,
             5);
  }
}

void Wagon::set_position(int x, int y, double arg) {
  x_ = x;
  y_ = y;
  angle_ = arg;
}
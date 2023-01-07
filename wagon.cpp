#include "wagon.h"

#include <cmath>

#define PI 3.14159265   

double radian(double deg) {
    return (deg * PI / 180.0); 
}

void Wagon::draw(cv::Mat background) {
    cv::Point2d p0(-side_ * cos(radian(angle_)) - -side_ * sin(radian(angle_)) + x_, 
                   -side_ * sin(radian(angle_)) + -side_ * cos(radian(angle_)) + y_);
    cv::Point2d p1(side_ * cos(radian(angle_)) - -side_ * sin(radian(angle_)) + x_, 
                   side_ * sin(radian(angle_)) + -side_ * cos(radian(angle_)) + y_);  
    cv::Point2d p2(side_ * cos(radian(angle_)) - side_ * sin(radian(angle_)) + x_, 
                   side_ * sin(radian(angle_)) + side_ * cos(radian(angle_)) + y_);
    cv::Point2d p3(-side_ * cos(radian(angle_)) - side_ * sin(radian(angle_)) + x_, 
                   -side_ * sin(radian(angle_)) + side_ * cos(radian(angle_)) + y_);         
    cv::Scalar red(0, 0, 255);

    cv::line(background, p0, p1, red);
    cv::line(background, p1, p2, red);   
    cv::line(background, p2, p3, red);      
    cv::line(background, p3, p0, red);                                     
}

void Wagon::setPosition(int x, int y, double arg) {
    x_ = x;
    y_ = y;
    angle_ = arg;
}
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "wagon.h"

int main() {
    cv::Mat background = cv::imread("../moleworm.jpg");
    Wagon wagon;
    wagon.setPosition(100, 100, 45.0);
    wagon.draw(background);
    cv::imshow("lab1", background);
    cv::waitKey(-1);
}
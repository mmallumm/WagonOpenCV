#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "wagon.h"

int main() {
    cv::Mat background = cv::imread("../moleworm.jpg");
    Wagon wagon(background, 30, 40);
    wagon.drive_1();
    wagon.drive_2();
}
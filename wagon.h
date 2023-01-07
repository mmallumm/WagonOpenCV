#include <opencv2/opencv.hpp> 

class Wagon {
public:
    Wagon(double side = 40) : side_(side) {};
    void draw(cv::Mat background);
    void setPosition(int x, int y, double arg);
    
private:
    const double side_;
    int x_ = 0;
    int y_ = 0;
    double angle_ = 0;
};
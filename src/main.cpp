#include <iostream>
#include <opencv2/opencv.hpp>

#include "demo/circle_demo.h"
#include "demo/image_demo.h"


using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char **argv) {

//    CircleDemo demo;
//    Circle C(Point2d(0, 0), 1);

    ImageDemo demo;

    demo.demo();


//    for (int i = 0; i < 100; i++) {
//        cout << demo.randOnCircleWithNoise(C) << endl;
//    }
    return 0;
}
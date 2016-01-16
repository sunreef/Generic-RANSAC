#include <iostream>
#include <opencv2/opencv.hpp>

#include "demo/circle_demo.h"
#include "demo/image_demo.h"


using namespace cv;
using std::cout;
using std::endl;

int main(int argc, char **argv) {

    CircleDemo demo;
    ImageDemo demo2;

    demo.demo();

    demo2.demo();

    return 0;
}
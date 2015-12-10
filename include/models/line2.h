//
// Created by antoinewdg on 11/11/15.
//

#ifndef OPENCV_BASE_LINE2_H
#define OPENCV_BASE_LINE2_H

#include <array>
#include <opencv2/core.hpp>


using std::array;
using cv::Point2f;

class Line2 {
public:
    Point2f n;
    float c;

    Line2(Point2f p, Point2f q) : n(q.y - p.y, p.x - q.x) {
        n /= cv::norm(n);
        c = n.dot(p);
    }

    float distanceTo(Point2f p) {
        return std::abs(n.dot(p) - c);
    }


};

#endif //OPENCV_BASE_LINE2_H

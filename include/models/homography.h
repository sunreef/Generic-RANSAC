//
// Created by victor on 14/12/15.
//

#ifndef GENERIC_RANSAC_HOMOGRAPHY_H
#define GENERIC_RANSAC_HOMOGRAPHY_H

#include <opencv2/core.hpp>
#include <iterator>

using cv::Point2d;

class Homography {


public:

    template<class Iterator>
    Homography(Iterator begin, Iterator end, bool &exists) {

    }

    template<class Iterator>
    double error(Iterator begin, Iterator end) {
        return 0;
    }

    double distance(Point2d p) {
        return 0;
    }
};

#endif //GENERIC_RANSAC_HOMOGRAPHY_H

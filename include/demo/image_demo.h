//
// Created by victor on 14/12/15.
//

#ifndef GENERIC_RANSAC_IMAGE_DEMO_H
#define GENERIC_RANSAC_IMAGE_DEMO_H


#include <vector>
#include <opencv2/features2d.hpp>
#include "util/image.h"
#include "../models/homography.h"
#include "../ransac.h"

class ImageDemo {


public:

    void demo();


    struct HomographyFromPoints {
        template<class Iterator>
        Homography operator()(Iterator begin, Iterator end, bool &exists) {
            exists = true;
            return Homography(begin, end);
        }
    };

    struct DistancePointFromHomography {
        double operator()(const Homography &H, Homography::Pair p) {
            return std::pow(cv::norm((Point2f)p.second - H(p.first)),2);
        }
    };

    struct HomographyError {
        template<class Iterator>
        double operator()(const Homography &H, Iterator begin, Iterator end) {
            return H.error;
        }
    };
};




#endif //GENERIC_RANSAC_IMAGE_DEMO_H

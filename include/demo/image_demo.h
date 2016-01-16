//
// Created by victor on 14/12/15.
//

#ifndef GENERIC_RANSAC_IMAGE_DEMO_H
#define GENERIC_RANSAC_IMAGE_DEMO_H


#include <vector>
#include <string>
#include <opencv2/features2d.hpp>
#include "util/image.h"
#include "../models/homography.h"
#include "../ransac.h"

using namespace std;

class ImageDemo {


public:

    void demo();
    Mat mergeImages(Mat &I1, Mat &I2);
    Mat findHomography(Mat I1, Mat I2);
    vector<Mat> findHomographies(vector<string> filenames);


    struct HomographyFromPoints {
        template<class Iterator>
        Homography operator()(Iterator begin, Iterator end, bool &exists) {
            exists = true;
            return Homography(begin, end);
        }
    };

    struct DistancePointFromHomography {
        double operator()(const Homography &H, Homography::Pair p) {
            return cv::norm((Point2f)p.second - H(p.first));
        }
    };

    struct HomographyError {
        template<class Iterator>
        double operator()(const Homography &H, Iterator begin, Iterator end) {
            long n = std::distance(begin, end);
            return H.error / n;
        }
    };
};




#endif //GENERIC_RANSAC_IMAGE_DEMO_H

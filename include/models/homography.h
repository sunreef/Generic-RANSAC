#ifndef GENERIC_RANSAC_HOMOGRAPHY_H
#define GENERIC_RANSAC_HOMOGRAPHY_H

#include <opencv2/core.hpp>
#include <utility>
#include <iostream>

using cv::Point2f;
using cv::Mat;


class Homography {


public:

    typedef std::pair<Point2f, Point2f> Pair;

    Homography() : H(3, 3, CV_32F) { }

    Homography(const Mat &H) : H(H) { }

    template<class Iterator>
    Homography(Iterator begin, Iterator end) : H(3, 3, CV_32F) {

        Mat A = createAMatrix(begin, end);



        cv::SVD::solveZ(A, h);

        error = cv::norm(A*h);
        for (int j = 0; j < 9; j++) {
            H.at<float>(j / 3, j % 3) = h.at<float>(0, j);
        }

    }


    Point2f operator()(const Point2f &p) const{
        Mat m(3, 1, CV_32F);
        m.at<float>(0, 0) = p.x;
        m.at<float>(1, 0) = p.y;
        m.at<float>(2, 0) = 1.f;

        Mat r = H * m;
        return Point2f(r.at<float>(0, 0) / r.at<float>(2, 0), r.at<float>(1, 0) / r.at<float>(2, 0));
    }


    Mat H;
    float error;

private:


    inline Mat axT(Pair p) {
        Mat x(1, 9, CV_32F);
        x.at<float>(0, 0) = -p.first.x;
        x.at<float>(0, 1) = -p.first.y;
        x.at<float>(0, 2) = -1.f;
        x.at<float>(0, 3) = 0.f;
        x.at<float>(0, 4) = 0.f;
        x.at<float>(0, 5) = 0.f;
        x.at<float>(0, 6) = p.first.x * p.second.x;
        x.at<float>(0, 7) = p.first.y * p.second.x;
        x.at<float>(0, 8) = p.second.x;

        return x;
    }

    inline Mat ayT(Pair p) {
        Mat x(1, 9, CV_32F);
        x.at<float>(0, 3) = -p.first.x;
        x.at<float>(0, 4) = -p.first.y;
        x.at<float>(0, 5) = -1.f;
        x.at<float>(0, 0) = 0.f;
        x.at<float>(0, 1) = 0.f;
        x.at<float>(0, 2) = 0.f;
        x.at<float>(0, 6) = p.first.x * p.second.y;
        x.at<float>(0, 7) = p.first.y * p.second.y;
        x.at<float>(0, 8) = p.second.y;

        return x;
    }

    template<class Iterator>
    Mat createAMatrix(Iterator begin, Iterator end) {
        long N = std::distance(begin, end);

        Mat A(2 * N, 9, CV_32F);

        int i = 0;
        for (Iterator it = begin; it != end; it++) {
            Mat l1(A.rowRange(2 * i, 2 * i + 1)), l2(A.rowRange(2 * i + 1, 2 * i + 2));
            axT(*it).copyTo(l1);
            ayT(*it).copyTo(l2);
            i++;
        }

        return A;
    }

    Mat h;

};

#endif //GENERIC_RANSAC_HOMOGRAPHY_H

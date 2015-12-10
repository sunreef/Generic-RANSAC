//
// Created by antoinewdg on 12/10/15.
//

#ifndef GENERIC_RANSAC_CIRCLE_H_H
#define GENERIC_RANSAC_CIRCLE_H_H

#include <cmath>
#include <opencv2/core.hpp>
#include <numeric>
#include <iterator>

using cv::Point2d;

class Circle {

public:

    Point2d c;
    double r;

    Circle() { }

    Circle(const Point2d &c, double r) : c(c), r(r) { }

    template<class Iterator>
    Circle(Iterator begin, Iterator end, bool &exists) {

        long N = std::distance(begin, end);
        if (N < 3) {
            exists = false;
            return;
        }

        Point2d M = std::accumulate(begin, end, Point2d(0.0, 0.0));
        M = (1.0 / N) * M;
        Point2d A(M);

        Point2d p;
        double Suu = 0, Suv = 0, Svv = 0, Suuu = 0, Suvv = 0, Svvv = 0, Svuu = 0;
        int i = 0;
        for (Iterator it = begin; it != end; it++) {
            p = *it - M;
            double uu = p.x * p.x, vv = p.y * p.y;
            Suu += uu;
            Svv += vv;
            Suv += p.x * p.y;
            Suuu += uu * p.x;
            Svvv += vv * p.y;
            Suvv += p.x * vv;
            Svuu += p.y * uu;
        }

        double alpha = 0.5 * (Suuu + Suvv), beta = 0.5 * (Svvv + Svuu),
                delta = Suu * Svv - Suv * Suv,
                deltaX = alpha * Svv - beta * Suv, deltaY = beta * Suu - alpha * Suv;

        if (delta == 0) {
            exists = false;
            return;
        }

        Point2d u(deltaX / delta, deltaY / delta);
        r = std::sqrt((u.x * u.x) + (u.y * u.y) + ((Suu + Svv) / N));
        c = u + M;

        exists = true;
    }

    template<class Iterator>
    double error(Iterator begin, Iterator end) {
        double error = 0;
        for (Iterator it = begin; it != end; it++) {
            error += std::pow(cv::norm(c - *it) - r, 2);
        }

        return error;
    }
};

#endif //GENERIC_RANSAC_CIRCLE_H_H

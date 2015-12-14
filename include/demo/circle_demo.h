//
// Created by antoinewdg on 12/10/15.
//

#ifndef GENERIC_RANSAC_CIRCLE_DEMO_H
#define GENERIC_RANSAC_CIRCLE_DEMO_H

#include <models/circle.h>
#include <random>
#include <vector>
#include "util/image.h"
#include "../ransac.h"

using std::vector;

class CircleDemo {
public:

    CircleDemo() : engine(std::random_device{}()), dis(), norm(0, 9) { }

    inline Point2d randOnCircle(const Circle &C) {
        double t = 2 * M_PI * dis(engine);
        return C.c + C.r * (Point2d(std::cos(t), std::sin(t)));
    }

    inline Point2d randOnePlane(double w, double h) {
        return Point2d(w * dis(engine), h * dis(engine));
    }

    inline Point2d noise() {
        return Point2d(norm(engine), norm(engine));
    }

    vector<Point2d> randOnCircleWithNoise(const Circle &C, int N);

    void demo();

private:
    std::uniform_real_distribution<double> dis;
    std::normal_distribution<double> norm;
    std::default_random_engine engine;
};

#endif //GENERIC_RANSAC_CIRCLE_DEMO_H

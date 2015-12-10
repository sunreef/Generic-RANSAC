#include "demo/circle_demo.h"

vector<Point2d> CircleDemo::randOnCircle(const Circle &C, int N) {
    vector<Point2d> points(N);
    for (int i = 0; i < N; i++) {
        points[i] = randOnCircle(C);
    }

    return points;
}

void CircleDemo::demo() {

    Circle C(Point2d(300, 300), 100);
    vector<Point2d> points = randOnCircle(C, 100);

    Image<Vec3b> img(Mat(600, 600, CV_8UC3, Scalar(255, 255, 255)));

    for (Point2d &p : points) {
        p += noise();
        circle(img, p, 2, Scalar(0, 255, 0), 2);
    }

    bool exists;
    Circle fit(points.begin(), points.end(), exists);
    if (exists) {
        circle(img, fit.c, std::round(fit.r), Scalar(255, 0, 0), 1);
    }

    imshow("ded", img);
    waitKey();
}

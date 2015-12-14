#include "demo/circle_demo.h"

vector<Point2d> CircleDemo::randOnCircleWithNoise(const Circle &C, int N) {
    vector<Point2d> points(N);
    for (int i = 0; i < N; i++) {
        points[i] = randOnCircle(C) + noise();
    }

    return points;
}

void CircleDemo::demo() {

    Circle C(Point2d(300, 300), 100);
    vector<Point2d> points = randOnCircleWithNoise(C, 100);

    Image<Vec3b> img(Mat(600, 600, CV_8UC3, Scalar(255, 255, 255)));

    for (int i = 0; i < 30; i++) {
        points.push_back(randOnePlane(600, 600));
    }

    for (Point2d &p : points) {
        circle(img, p, 2, Scalar(0, 255, 0), 2);
    }

    bool exists;
    Circle fit(points.begin(), points.end(), exists);



    RANSAC<Point2d, Circle, 10> r(fit, points, 20, 10, 20);
    fit = r.findBestFit();

    if (exists) {
        circle(img, fit.c, std::round(fit.r), Scalar(255, 0, 0), 1);
    }

    std::cout << "error: " << fit.error(points.begin(), points.end()) << std::endl;
    imshow("ded", img);
    waitKey();
}

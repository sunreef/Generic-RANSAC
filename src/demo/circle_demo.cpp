#include "demo/circle_demo.h"

vector<Point2d> CircleDemo::randOnCircleWithNoise(const Circle &C, int N) {
    vector<Point2d> points(N);
    for (int i = 0; i < N; i++) {
        points[i] = randOnCircle(C) + noise();
    }

    return points;
}

void CircleDemo::demo() {

    for (int t = 0; t < 100; t++) {
        Circle C(Point2d(300, 300), 100);
        vector<Point2d> points = randOnCircleWithNoise(C, 100);

        Image<Vec3b> img(Mat(600, 600, CV_8UC3, Scalar(255, 255, 255)));

        for (int i = 0; i < 30; i++) {
            points.push_back(randOnePlane(600, 600));
        }


        bool exists;
        Circle fit(points.begin(), points.end(), exists);


        RANSAC<Circle, Point2d, CircleFromPoints, DistancePointFromCircle, CircleError> r(3, points, 100, 20, 40,
                                                                                          CircleFromPoints(),
                                                                                          DistancePointFromCircle(),
                                                                                          CircleError());
        fit = r.findBestFit();
        if (exists) {
            circle(img, fit.c, std::round(fit.r), Scalar(255, 0, 0), 1);
        }
        for (const Point2d &p : r.getInliers()) {
            circle(img, p, 2, Scalar(255, 0, 0), 2);
        }
        for (Point2d &p : points) {
            circle(img, p, 2, Scalar(0, 255, 0), 2);
//        imshow("ded", img);
//        waitKey();
        }


        std::cout << "error: " << fit.error(points.begin(), points.end()) << std::endl;
        imshow("ded", img);
        waitKey();
    }
}

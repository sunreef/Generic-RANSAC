#include <gtest/gtest.h>
#include <vector>
#include "models/homography.h"

typedef Homography::Pair Pair;
using std::vector;

TEST(Homography, basicCase) {
    vector<Pair> pairs = {
            Pair(Point2f(0, 0), Point2f(0, 0)),
            Pair(Point2f(1, 0), Point2f(1, 0)),
            Pair(Point2f(0, 1), Point2f(0, 1)),
            Pair(Point2f(1, 1), Point2f(1, 1)),
    };

    Homography H(pairs.begin(), pairs.end());

    Point2f m(2, 2), p(H(m));
    ASSERT_NEAR(2.0, p.x, 1e-6);
    ASSERT_NEAR(2.0, p.y, 1e-6);
}

TEST(Homography, classicCase) {
    vector<Pair> pairs = {
            Pair(Point2f(0, 0), Point2f(0, 1)),
            Pair(Point2f(2, 0), Point2f(2, 0)),
            Pair(Point2f(0, 2), Point2f(0, 2)),
            Pair(Point2f(2, 2), Point2f(2, 3)),
    };

    Homography H(pairs.begin(), pairs.end());

    Point2f m(2, 2), p(H(m));
    ASSERT_NEAR(2.0, p.x, 1e-6);
    ASSERT_NEAR(3.0, p.y, 1e-6);

    p = H(Point2f(0, 0));
    ASSERT_NEAR(0, p.x, 1e-6);
    ASSERT_NEAR(1, p.y, 1e-6);

    p = H(Point2f(0, 2));
    ASSERT_NEAR(0, p.x, 1e-6);
    ASSERT_NEAR(2, p.y, 1e-6);

    p = H(Point2f(2, 0));
    ASSERT_NEAR(2, p.x, 1e-6);
    ASSERT_NEAR(0, p.y, 1e-6);


}

TEST(Homography, leastSquare) {
    vector<Pair> pairs = {
            Pair(Point2f(0, 0), Point2f(0, 0)),
            Pair(Point2f(1, 0), Point2f(1, 0)),
            Pair(Point2f(0, 1), Point2f(0, 1)),
            Pair(Point2f(1, 1), Point2f(1, 1)),
            Pair(Point2f(0, 2), Point2f(0.1, 2))
    };

    Homography H(pairs.begin(), pairs.end());

    Point2f m(2, 2), p(H(m));
    ASSERT_NEAR(2.0, p.x, 0.1);
    ASSERT_NEAR(2.0, p.y, 0.1);


}
#include <gtest/gtest.h>
#include <vector>
#include "models/circle.h"


using std::vector;

TEST(Circle, impossibleCases) {
    vector<Point2d> points;
    bool exists;

    exists = true;
    Circle C(points.begin(), points.end(), exists);
    ASSERT_FALSE(exists);

    exists = true;
    points = {Point2d(1, 1), Point2d(2, 2)};
    C = Circle(points.begin(), points.end(), exists);
    ASSERT_FALSE(exists);

    exists = true;
    points = {Point2d(1, 1), Point2d(2, 2), Point2d(3, 3)};
    C = Circle(points.begin(), points.end(), exists);
    ASSERT_FALSE(exists);


}

TEST(Circle, from3Points) {
    vector<Point2d> points;
    bool exists;
    Circle C;

    exists = false;
    points = {Point2d(1, 1), Point2d(3, 3), Point2d(1, 3)};
    C = Circle(points.begin(), points.end(), exists);
    ASSERT_TRUE(exists);
    ASSERT_DOUBLE_EQ(std::sqrt(2), C.r);
    ASSERT_DOUBLE_EQ(2.0, C.c.x);
    ASSERT_DOUBLE_EQ(2.0, C.c.y);
}

TEST(Circle, fromNPoints) {
    vector<Point2d> points;
    bool exists;
    Circle C;

    exists = false;
    points = {Point2d(1, 1), Point2d(3, 3), Point2d(1, 3), Point2d(3, 1)};
    C = Circle(points.begin(), points.end(), exists);
    ASSERT_TRUE(exists);
    ASSERT_DOUBLE_EQ(std::sqrt(2), C.r);
    ASSERT_DOUBLE_EQ(2.0, C.c.x);
    ASSERT_DOUBLE_EQ(2.0, C.c.y);

    exists = false;
    points = {Point2d(1, 1), Point2d(3.1, 3.1), Point2d(1, 3), Point2d(3, 1)};
    C = Circle(points.begin(), points.end(), exists);
    ASSERT_TRUE(exists);
//    ASSERT_DOUBLE_EQ(std::sqrt(2), C.r);
//    ASSERT_DOUBLE_EQ(2.0, C.c.x);
//    ASSERT_DOUBLE_EQ(2.0, C.c.y);
}
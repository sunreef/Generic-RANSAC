#include <gtest/gtest.h>
#include "models/line2.h"

TEST(Line2, Construction) {
    Line2 line(Point2f(1, 1), Point2f(1, 0));
    ASSERT_EQ(Point2f(-1, 0), line.n);

    line = Line2(Point2f(0, 0), Point2f(1, 1));
    ASSERT_EQ(Point2f(1.0 / std::sqrt(2), -1.0 / std::sqrt(2)), line.n);
}

TEST(Line2, distanceFromPoint) {
    Line2 line(Point2f(1, 1), Point2f(1, 0));
    ASSERT_FLOAT_EQ(1, line.distanceTo(Point2f(0, 0)));
    ASSERT_FLOAT_EQ(2, line.distanceTo(Point2f(3, -4)));

    line = Line2(Point2f(0, 0), Point2f(1, 1));

    ASSERT_FLOAT_EQ(1 / std::sqrt(2), line.distanceTo(Point2f(1, 0)));
    ASSERT_FLOAT_EQ(0, line.distanceTo(Point2f(-3, -3)));
}
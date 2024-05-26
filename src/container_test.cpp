#include <container.h>
#include <gtest/gtest.h>

struct Point {
  int x, y;
};

TEST(container, TestingGetElement) {
    Container<char, int, double, Point> c('a', 4, 3.14, Point{12, 1});

    EXPECT_EQ(c.getElement<char>(0), 'a');
    EXPECT_EQ(c.getElement<int>(1), 4);
    EXPECT_DOUBLE_EQ(c.getElement<double>(2), 3.14);
    EXPECT_EQ(c.getElement<Point>(3).x, 12);
}



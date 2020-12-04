#include <rt/math/Vec3.h>
#include <rt/math/Ray.h>
#include "gtest/gtest.h"

TEST(ray, Constructor) {
    rt::Vec3 origin(1, 2, 3);
    rt::Vec3 direction(4, 5, 6);

    rt::Ray ray(origin, direction);

    EXPECT_EQ(ray.direction, direction);
    EXPECT_EQ(ray.origin, origin);
}

TEST(ray, AtCorectness) {
    rt::Vec3 origin(1, 2, 3);
    rt::Vec3 direction(4, 5, 6);
    double time = 0.5;
    rt::Ray ray(origin, direction);

    rt::Vec3 at = ray(time);

    EXPECT_DOUBLE_EQ(at.x, 3);
    EXPECT_DOUBLE_EQ(at.y, 4.5);
    EXPECT_DOUBLE_EQ(at.z, 6);
}

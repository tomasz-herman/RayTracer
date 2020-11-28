#include <rt/math/vec3.h>
#include <rt/math/ray.h>
#include "gtest/gtest.h"

TEST(ray, Constructor) {
    rt::vec3 origin(1, 2, 3);
    rt::vec3 direction(4, 5, 6);

    rt::ray ray(origin, direction);

    EXPECT_EQ(ray.direction, direction);
    EXPECT_EQ(ray.origin, origin);
}

TEST(ray, AtCorectness) {
    rt::vec3 origin(1, 2, 3);
    rt::vec3 direction(4, 5, 6);
    double time = 0.5;
    rt::ray ray(origin, direction);

    rt::vec3 at = ray(time);

    EXPECT_DOUBLE_EQ(at.x, 3);
    EXPECT_DOUBLE_EQ(at.y, 4.5);
    EXPECT_DOUBLE_EQ(at.z, 6);
}

#include "gtest/gtest.h"
#include "rt/math/vec3.h"

TEST(vec3, NoArgsConstructor) {
    rt::vec3 vec;
    EXPECT_EQ(vec.x, 0);
    EXPECT_EQ(vec.y, 0);
    EXPECT_EQ(vec.z, 0);
}

TEST(vec3, ArgsConstructor) {
    rt::vec3 vec(1, 2, 3);
    EXPECT_EQ(vec.x, 1);
    EXPECT_EQ(vec.y, 2);
    EXPECT_EQ(vec.z, 3);
}
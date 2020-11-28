#include "gtest/gtest.h"
#include "rt/math/vec3.h"

TEST(vec3, NoArgsConstructor) {
    rt::vec3 vec;
    EXPECT_DOUBLE_EQ(vec.x, 0);
    EXPECT_DOUBLE_EQ(vec.y, 0);
    EXPECT_DOUBLE_EQ(vec.z, 0);
}

TEST(vec3, ArgsConstructor) {
    rt::vec3 vec(1, 2, 3);
    EXPECT_DOUBLE_EQ(vec.x, 1);
    EXPECT_DOUBLE_EQ(vec.y, 2);
    EXPECT_DOUBLE_EQ(vec.z, 3);
}

TEST(vec3, LengthSquaredCorectness) {
    rt::vec3 vec(1, 2, 3);

    double length_squared = vec.length_squared();

    EXPECT_DOUBLE_EQ(length_squared, 14);
}

TEST(vec3, LengthCorectness) {
    rt::vec3 vec(3, 2, 6);

    double length = vec.length();

    EXPECT_DOUBLE_EQ(length, 7);
}

TEST(vec3, DistanceCorectness) {
    rt::vec3 a(8, 0, 5);
    rt::vec3 b(5, -2, -1);

    double distance = a.distance(b);

    EXPECT_DOUBLE_EQ(distance, 7);
}

TEST(vec3, DotProductCorectness) {
    rt::vec3 a(8, 0, 5);
    rt::vec3 b(5, -2, -1);

    double dot = a.dot(b);

    EXPECT_DOUBLE_EQ(dot, 35);
}

TEST(vec3, OperatorEqualsShouldReturnFalse) {
    rt::vec3 a(8, 0, 5);
    rt::vec3 b(5, -2, -1);
    EXPECT_FALSE(a == b);
}

TEST(vec3, OperatorEqualsShouldReturnTrue) {
    rt::vec3 a(8, 0, 5);
    rt::vec3 b(8, 0, 5);
    EXPECT_TRUE(a == b);
}

TEST(vec3, OperatorNotEqualsShouldReturnTrue) {
    rt::vec3 a(8, 0, 5);
    rt::vec3 b(5, -2, -1);
    EXPECT_TRUE(a != b);
}

TEST(vec3, OperatorNotEqualsShouldReturnFalse) {
    rt::vec3 a(8, 0, 5);
    rt::vec3 b(8, 0, 5);
    EXPECT_FALSE(a != b);
}

TEST(vec3, NormalizedCorectness) {
    rt::vec3 vec(3, 2, 6);

    rt::vec3 norm = vec.normalized();

    EXPECT_DOUBLE_EQ(norm.x, 3.0 / 7.0);
    EXPECT_DOUBLE_EQ(norm.y, 2.0 / 7.0);
    EXPECT_DOUBLE_EQ(norm.z, 6.0 / 7.0);
}

TEST(vec3, CrossProductCorectness) {
    rt::vec3 a(3, -3, 1);
    rt::vec3 b(4, 9, 2);

    rt::vec3 cross = a.cross(b);

    EXPECT_DOUBLE_EQ(cross.x, -15);
    EXPECT_DOUBLE_EQ(cross.y, -2);
    EXPECT_DOUBLE_EQ(cross.z, 39);
}


TEST(vec3, OperatorUnaryMinusCorectness) {
    rt::vec3 vec(1, 2, 3);

    rt::vec3 neg = -vec;

    EXPECT_DOUBLE_EQ(neg.x, -1);
    EXPECT_DOUBLE_EQ(neg.y, -2);
    EXPECT_DOUBLE_EQ(neg.z, -3);
}

TEST(vec3, OperatorMinusCorectness) {
    rt::vec3 a(1, 2, 3);
    rt::vec3 b(2, 2, 2);

    rt::vec3 minus = a - b;

    EXPECT_DOUBLE_EQ(minus.x, -1);
    EXPECT_DOUBLE_EQ(minus.y, 0);
    EXPECT_DOUBLE_EQ(minus.z, 1);
}

TEST(vec3, OperatorPlusCorectness) {
    rt::vec3 a(1, 2, 3);
    rt::vec3 b(2, -2, 2);

    rt::vec3 plus = a + b;

    EXPECT_DOUBLE_EQ(plus.x, 3);
    EXPECT_DOUBLE_EQ(plus.y, 0);
    EXPECT_DOUBLE_EQ(plus.z, 5);
}

TEST(vec3, OperatorMultiplyCorectness) {
    rt::vec3 a(1, 2, 3);
    double b = 3;

    rt::vec3 times = a * b;

    EXPECT_DOUBLE_EQ(times.x, 3);
    EXPECT_DOUBLE_EQ(times.y, 6);
    EXPECT_DOUBLE_EQ(times.z, 9);
}

TEST(vec3, OperatorDivideCorectness) {
    rt::vec3 a(1, 2, 3);
    double b = 3;

    rt::vec3 divided = a / b;

    EXPECT_DOUBLE_EQ(divided.x, 1.0 / 3.0);
    EXPECT_DOUBLE_EQ(divided.y, 2.0 / 3.0);
    EXPECT_DOUBLE_EQ(divided.z, 1);
}


TEST(vec3, OperatorMinusAssignCorectness) {
    rt::vec3 a(1, 2, 3);
    rt::vec3 b(2, 2, 2);

    a -= b;

    EXPECT_DOUBLE_EQ(a.x, -1);
    EXPECT_DOUBLE_EQ(a.y, 0);
    EXPECT_DOUBLE_EQ(a.z, 1);
}

TEST(vec3, OperatorPlusAssignCorectness) {
    rt::vec3 a(1, 2, 3);
    rt::vec3 b(2, -2, 2);

    a += b;

    EXPECT_DOUBLE_EQ(a.x, 3);
    EXPECT_DOUBLE_EQ(a.y, 0);
    EXPECT_DOUBLE_EQ(a.z, 5);
}

TEST(vec3, OperatorMultiplyAssignCorectness) {
    rt::vec3 a(1, 2, 3);
    double b = 3;

    a *= b;

    EXPECT_DOUBLE_EQ(a.x, 3);
    EXPECT_DOUBLE_EQ(a.y, 6);
    EXPECT_DOUBLE_EQ(a.z, 9);
}

TEST(vec3, OperatorDivideAssignCorectness) {
    rt::vec3 a(1, 2, 3);
    double b = 3;

    a /= b;

    EXPECT_DOUBLE_EQ(a.x, 1.0 / 3.0);
    EXPECT_DOUBLE_EQ(a.y, 2.0 / 3.0);
    EXPECT_DOUBLE_EQ(a.z, 1);
}

TEST(vec3, OperatorOstreamCorectness) {
    rt::vec3 vec(1, 2, 3);

    std::ostringstream stream;
    stream << vec;
    std::string str = stream.str();

    EXPECT_STREQ(str.c_str(), "(x:1, y:2, z:3)");
}
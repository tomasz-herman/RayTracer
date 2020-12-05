#include <rt/math/Color3.h>
#include "gtest/gtest.h"

TEST(color, GrayConstructor) {
    rt::Color3 gray(0.45);

    EXPECT_DOUBLE_EQ(gray.r, 0.45);
    EXPECT_DOUBLE_EQ(gray.g, 0.45);
    EXPECT_DOUBLE_EQ(gray.b, 0.45);
}

TEST(color, NoArgsConstructor) {
    rt::Color3 black;

    EXPECT_DOUBLE_EQ(black.r, 0);
    EXPECT_DOUBLE_EQ(black.g, 0);
    EXPECT_DOUBLE_EQ(black.b, 0);
}

TEST(color, RGBConstructor) {
    rt::Color3 gray(0.45, 0.6, 0.75);

    EXPECT_DOUBLE_EQ(gray.r, 0.45);
    EXPECT_DOUBLE_EQ(gray.g, 0.6);
    EXPECT_DOUBLE_EQ(gray.b, 0.75);
}

TEST(color, RGBIntegersConstructor) {
    rt::Color3 color(0, 1, 45);

    EXPECT_DOUBLE_EQ(color.r, 0.0 / 255.0);
    EXPECT_DOUBLE_EQ(color.g, 1.0 / 255.0);
    EXPECT_DOUBLE_EQ(color.b, 45.0 / 255.0);
}

TEST(color, FromHsb) {
    rt::Color3 color = rt::Color3::hsb(60, 0.5, 0.6); //olive

    EXPECT_DOUBLE_EQ(color.r, 0.6);
    EXPECT_DOUBLE_EQ(color.g, 0.6);
    EXPECT_DOUBLE_EQ(color.b, 0.3);
}

TEST(color, DarkerColorHasLessRgbValue) {
    rt::Color3 color(0.6, 0.6, 0.3);

    rt::Color3 darker = color.darker();

    EXPECT_LT(darker.r, color.r);
    EXPECT_LT(darker.g, color.g);
    EXPECT_LT(darker.b, color.b);
}

TEST(color, BrighterColorHasMoreRgbValue) {
    rt::Color3 color(0.6, 0.6, 0.3);

    rt::Color3 brighter = color.brighter();

    EXPECT_GT(brighter.r, color.r);
    EXPECT_GT(brighter.g, color.g);
    EXPECT_GT(brighter.b, color.b);
}

TEST(color, DesaturatedColorIsShiftedTowardsGray) {
    rt::Color3 color(0.6, 0.8, 0.3);

    rt::Color3 desaturated = color.desaturated();

    EXPECT_GT(desaturated.r, color.r);
    EXPECT_EQ(desaturated.g, color.g);
    EXPECT_GT(desaturated.b, color.b);
}

TEST(color, SaturatedColorIsShiftedAwayFromGray) {
    rt::Color3 color(0.6, 0.8, 0.3);

    rt::Color3 saturated = color.saturated();

    EXPECT_LT(saturated.r, color.r);
    EXPECT_EQ(saturated.g, color.g);
    EXPECT_LT(saturated.b, color.b);
}

TEST(color, GrayscaleUses299R587G114BFormula) {
    rt::Color3 color(30, 128, 255);

    rt::Color3 gray = color.grayscale();

    EXPECT_DOUBLE_EQ(gray.r, 113.176 / 255.0);
    EXPECT_DOUBLE_EQ(gray.g, 113.176 / 255.0);
    EXPECT_DOUBLE_EQ(gray.b, 113.176 / 255.0);
}

TEST(color, InvertCorectness) {
    rt::Color3 color(0.3, 0.5, 0.7);

    rt::Color3 inverted = color.inverted();

    EXPECT_DOUBLE_EQ(inverted.r, 0.7);
    EXPECT_DOUBLE_EQ(inverted.g, 0.5);
    EXPECT_DOUBLE_EQ(inverted.b, 0.3);
}

TEST(color, InterpolatedCorectness) {
    rt::Color3 RED(1.0, 0.0, 0.0);
    rt::Color3 BLUE(0.0, 0.0, 1.0);
    double factor = 0.6;

    rt::Color3 interpolated = RED.interpolated(BLUE, factor);

    EXPECT_DOUBLE_EQ(interpolated.r, 0.4);
    EXPECT_DOUBLE_EQ(interpolated.g, 0.0);
    EXPECT_DOUBLE_EQ(interpolated.b, 0.6);
}

TEST(color, DeriveCanShiftHue) {
    rt::Color3 RED(1.0, 0.0, 0.0);
    double hue_shift = 180;

    rt::Color3 derived = RED.derive(hue_shift);

    EXPECT_DOUBLE_EQ(derived.r, 0.0);
    EXPECT_DOUBLE_EQ(derived.g, 1.0);
    EXPECT_DOUBLE_EQ(derived.b, 1.0);
}

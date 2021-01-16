#ifndef RAYTRACER_COLOR3_H
#define RAYTRACER_COLOR3_H

#include <ostream>
#include <array>
#include <rt/utils/Printable.h>

namespace rt {
    struct Color3 : public Printable {
        static constexpr double DARKER_BRIGHTER_FACTOR = 0.7;
        static constexpr double SATURATE_DESATURATE_FACTOR = 0.7;

        double r, g, b;

        Color3();
        explicit Color3(double gray);
        Color3(double r, double g, double b);
        Color3(int r, int g, int b);

        Color3& add(const Color3& other);
        Color3& sub(const Color3& other);
        Color3& mul(const Color3 &other);
        Color3& mul(double other);
        Color3& div(double other);

        friend Color3 operator+(Color3 left, const Color3 &right);
        friend Color3 operator-(Color3 left, const Color3 &right);
        friend Color3 operator*(Color3 left, const Color3 &right);
        friend Color3 operator*(Color3 left, double right);
        friend Color3 operator/(Color3 left, double right);

        Color3& operator+=(const Color3& other);
        Color3& operator-=(const Color3& other);
        Color3& operator*=(const Color3& other);
        Color3& operator*=(double other);
        Color3& operator/=(double other);

        bool operator==(const Color3& other) const;
        bool operator!=(const Color3& other) const;

        void print(std::ostream& stream, int indent) const override;

        static std::array<double, 3> hsb_to_rgb(double hue, double saturation, double brightness);
        static std::array<double, 3> rgb_to_hsv(double r, double g, double b);

        static Color3 rgb(double r, double g, double b);
        static Color3 hsb(double h, double s, double b);

        [[nodiscard]] Color3 derive(double hue_shift, double saturation_factor = 1.0, double brightness_factor = 1.0) const;

        [[nodiscard]] Color3 darker() const;
        [[nodiscard]] Color3 brighter() const;
        [[nodiscard]] Color3 saturated() const;
        [[nodiscard]] Color3 desaturated() const;
        [[nodiscard]] Color3 grayscale() const;
        [[nodiscard]] Color3 inverted() const;
        [[nodiscard]] Color3 gamma_correction(double gamma) const;

        [[nodiscard]] Color3 interpolated(const Color3& other, double factor) const;

        static Color3 ALICEBLUE();
        static Color3 ANTIQUEWHITE();
        static Color3 AQUA();
        static Color3 AQUAMARINE();
        static Color3 AZURE();
        static Color3 BEIGE();
        static Color3 BISQUE();
        static Color3 BLACK();
        static Color3 BLANCHEDALMOND();
        static Color3 BLUE();
        static Color3 BLUEVIOLET();
        static Color3 BROWN();
        static Color3 BURLYWOOD();
        static Color3 CADETBLUE();
        static Color3 CHARTREUSE();
        static Color3 CHOCOLATE();
        static Color3 CORAL();
        static Color3 CORNFLOWERBLUE();
        static Color3 CORNSILK();
        static Color3 CRIMSON();
        static Color3 CYAN();
        static Color3 DARKBLUE();
        static Color3 DARKCYAN();
        static Color3 DARKGOLDENROD();
        static Color3 DARKGRAY();
        static Color3 DARKGREEN();
        static Color3 DARKKHAKI();
        static Color3 DARKMAGENTA();
        static Color3 DARKOLIVEGREEN();
        static Color3 DARKORANGE();
        static Color3 DARKORCHID();
        static Color3 DARKRED();
        static Color3 DARKSALMON();
        static Color3 DARKSEAGREEN();
        static Color3 DARKSLATEBLUE();
        static Color3 DARKSLATEGRAY();
        static Color3 DARKTURQUOISE();
        static Color3 DARKVIOLET();
        static Color3 DEEPPINK();
        static Color3 DEEPSKYBLUE();
        static Color3 DIMGRAY();
        static Color3 DODGERBLUE();
        static Color3 FIREBRICK();
        static Color3 FLORALWHITE();
        static Color3 FORESTGREEN();
        static Color3 FUCHSIA();
        static Color3 GAINSBORO();
        static Color3 GHOSTWHITE();
        static Color3 GOLD();
        static Color3 GOLDENROD();
        static Color3 GRAY();
        static Color3 GREEN();
        static Color3 GREENYELLOW();
        static Color3 HONEYDEW();
        static Color3 HOTPINK();
        static Color3 INDIANRED();
        static Color3 INDIGO();
        static Color3 IVORY();
        static Color3 KHAKI();
        static Color3 LAVENDER();
        static Color3 LAVENDERBLUSH();
        static Color3 LAWNGREEN();
        static Color3 LEMONCHIFFON();
        static Color3 LIGHTBLUE();
        static Color3 LIGHTCORAL();
        static Color3 LIGHTCYAN();
        static Color3 LIGHTGOLDENRODYELLOW();
        static Color3 LIGHTGRAY();
        static Color3 LIGHTGREEN();
        static Color3 LIGHTPINK();
        static Color3 LIGHTSALMON();
        static Color3 LIGHTSEAGREEN();
        static Color3 LIGHTSKYBLUE();
        static Color3 LIGHTSLATEGRAY();
        static Color3 LIGHTSTEELBLUE();
        static Color3 LIGHTYELLOW();
        static Color3 LIME();
        static Color3 LIMEGREEN();
        static Color3 LINEN();
        static Color3 MAGENTA();
        static Color3 MAROON();
        static Color3 MEDIUMAQUAMARINE();
        static Color3 MEDIUMBLUE();
        static Color3 MEDIUMORCHID();
        static Color3 MEDIUMPURPLE();
        static Color3 MEDIUMSEAGREEN();
        static Color3 MEDIUMSLATEBLUE();
        static Color3 MEDIUMSPRINGGREEN();
        static Color3 MEDIUMTURQUOISE();
        static Color3 MEDIUMVIOLETRED();
        static Color3 MIDNIGHTBLUE();
        static Color3 MINTCREAM();
        static Color3 MISTYROSE();
        static Color3 MOCCASIN();
        static Color3 NAVAJOWHITE();
        static Color3 NAVY();
        static Color3 OLDLACE();
        static Color3 OLIVE();
        static Color3 OLIVEDRAB();
        static Color3 ORANGE();
        static Color3 ORANGERED();
        static Color3 ORCHID();
        static Color3 PALEGOLDENROD();
        static Color3 PALEGREEN();
        static Color3 PALETURQUOISE();
        static Color3 PALEVIOLETRED();
        static Color3 PAPAYAWHIP();
        static Color3 PEACHPUFF();
        static Color3 PERU();
        static Color3 PINK();
        static Color3 PLUM();
        static Color3 POWDERBLUE();
        static Color3 PURPLE();
        static Color3 RED();
        static Color3 ROSYBROWN();
        static Color3 ROYALBLUE();
        static Color3 SADDLEBROWN();
        static Color3 SALMON();
        static Color3 SANDYBROWN();
        static Color3 SEAGREEN();
        static Color3 SEASHELL();
        static Color3 SIENNA();
        static Color3 SILVER();
        static Color3 SKYBLUE();
        static Color3 SLATEBLUE();
        static Color3 SLATEGRAY();
        static Color3 SNOW();
        static Color3 SPRINGGREEN();
        static Color3 STEELBLUE();
        static Color3 TAN();
        static Color3 TEAL();
        static Color3 THISTLE();
        static Color3 TOMATO();
        static Color3 TURQUOISE();
        static Color3 VIOLET();
        static Color3 WHEAT();
        static Color3 WHITE();
        static Color3 WHITESMOKE();
        static Color3 YELLOW();
        static Color3 YELLOWGREEN();
    };
}

#endif //RAYTRACER_COLOR3_H

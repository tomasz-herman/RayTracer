#ifndef RAYTRACER_COLOR3_H
#define RAYTRACER_COLOR3_H

#include <ostream>
#include <array>

namespace rt {
    struct color3 {
        static constexpr double DARKER_BRIGHTER_FACTOR = 0.7;
        static constexpr double SATURATE_DESATURATE_FACTOR = 0.7;

        double r, g, b;

        color3();
        explicit color3(double gray);
        color3(double r, double g, double b);
        color3(int r, int g, int b);

        color3& add(const color3& other);
        color3& sub(const color3& other);
        color3& mul(double other);
        color3& div(double other);

        friend color3 operator+(color3 left, const color3 &right);
        friend color3 operator-(color3 left, const color3 &right);
        friend color3 operator*(color3 left, double right);
        friend color3 operator/(color3 left, double right);

        color3& operator+=(const color3& other);
        color3& operator-=(const color3& other);
        color3& operator*=(float other);
        color3& operator/=(float other);

        bool operator==(const color3& other) const;
        bool operator!=(const color3& other) const;

        friend std::ostream &operator<<(std::ostream &stream, const color3 &color);

        static std::array<double, 3> hsb_to_rgb(double hue, double saturation, double brightness);
        static std::array<double, 3> rgb_to_hsv(double r, double g, double b);

        static color3 rgb(double r, double g, double b);
        static color3 hsb(double h, double s, double b);

        [[nodiscard]] color3 derive(double hue_shift, double saturation_factor, double brightness_factor) const;

        [[nodiscard]] color3 darker() const;
        [[nodiscard]] color3 brighter() const;
        [[nodiscard]] color3 saturated() const;
        [[nodiscard]] color3 desaturated() const;
        [[nodiscard]] color3 grayscale() const;
        [[nodiscard]] color3 inverted() const;

        [[nodiscard]] color3 interpolated(const color3& other, double factor) const;

        static color3 ALICEBLUE();
        static color3 ANTIQUEWHITE();
        static color3 AQUA();
        static color3 AQUAMARINE();
        static color3 AZURE();
        static color3 BEIGE();
        static color3 BISQUE();
        static color3 BLACK();
        static color3 BLANCHEDALMOND();
        static color3 BLUE();
        static color3 BLUEVIOLET();
        static color3 BROWN();
        static color3 BURLYWOOD();
        static color3 CADETBLUE();
        static color3 CHARTREUSE();
        static color3 CHOCOLATE();
        static color3 CORAL();
        static color3 CORNFLOWERBLUE();
        static color3 CORNSILK();
        static color3 CRIMSON();
        static color3 CYAN();
        static color3 DARKBLUE();
        static color3 DARKCYAN();
        static color3 DARKGOLDENROD();
        static color3 DARKGRAY();
        static color3 DARKGREEN();
        static color3 DARKKHAKI();
        static color3 DARKMAGENTA();
        static color3 DARKOLIVEGREEN();
        static color3 DARKORANGE();
        static color3 DARKORCHID();
        static color3 DARKRED();
        static color3 DARKSALMON();
        static color3 DARKSEAGREEN();
        static color3 DARKSLATEBLUE();
        static color3 DARKSLATEGRAY();
        static color3 DARKTURQUOISE();
        static color3 DARKVIOLET();
        static color3 DEEPPINK();
        static color3 DEEPSKYBLUE();
        static color3 DIMGRAY();
        static color3 DODGERBLUE();
        static color3 FIREBRICK();
        static color3 FLORALWHITE();
        static color3 FORESTGREEN();
        static color3 FUCHSIA();
        static color3 GAINSBORO();
        static color3 GHOSTWHITE();
        static color3 GOLD();
        static color3 GOLDENROD();
        static color3 GRAY();
        static color3 GREEN();
        static color3 GREENYELLOW();
        static color3 HONEYDEW();
        static color3 HOTPINK();
        static color3 INDIANRED();
        static color3 INDIGO();
        static color3 IVORY();
        static color3 KHAKI();
        static color3 LAVENDER();
        static color3 LAVENDERBLUSH();
        static color3 LAWNGREEN();
        static color3 LEMONCHIFFON();
        static color3 LIGHTBLUE();
        static color3 LIGHTCORAL();
        static color3 LIGHTCYAN();
        static color3 LIGHTGOLDENRODYELLOW();
        static color3 LIGHTGRAY();
        static color3 LIGHTGREEN();
        static color3 LIGHTPINK();
        static color3 LIGHTSALMON();
        static color3 LIGHTSEAGREEN();
        static color3 LIGHTSKYBLUE();
        static color3 LIGHTSLATEGRAY();
        static color3 LIGHTSTEELBLUE();
        static color3 LIGHTYELLOW();
        static color3 LIME();
        static color3 LIMEGREEN();
        static color3 LINEN();
        static color3 MAGENTA();
        static color3 MAROON();
        static color3 MEDIUMAQUAMARINE();
        static color3 MEDIUMBLUE();
        static color3 MEDIUMORCHID();
        static color3 MEDIUMPURPLE();
        static color3 MEDIUMSEAGREEN();
        static color3 MEDIUMSLATEBLUE();
        static color3 MEDIUMSPRINGGREEN();
        static color3 MEDIUMTURQUOISE();
        static color3 MEDIUMVIOLETRED();
        static color3 MIDNIGHTBLUE();
        static color3 MINTCREAM();
        static color3 MISTYROSE();
        static color3 MOCCASIN();
        static color3 NAVAJOWHITE();
        static color3 NAVY();
        static color3 OLDLACE();
        static color3 OLIVE();
        static color3 OLIVEDRAB();
        static color3 ORANGE();
        static color3 ORANGERED();
        static color3 ORCHID();
        static color3 PALEGOLDENROD();
        static color3 PALEGREEN();
        static color3 PALETURQUOISE();
        static color3 PALEVIOLETRED();
        static color3 PAPAYAWHIP();
        static color3 PEACHPUFF();
        static color3 PERU();
        static color3 PINK();
        static color3 PLUM();
        static color3 POWDERBLUE();
        static color3 PURPLE();
        static color3 RED();
        static color3 ROSYBROWN();
        static color3 ROYALBLUE();
        static color3 SADDLEBROWN();
        static color3 SALMON();
        static color3 SANDYBROWN();
        static color3 SEAGREEN();
        static color3 SEASHELL();
        static color3 SIENNA();
        static color3 SILVER();
        static color3 SKYBLUE();
        static color3 SLATEBLUE();
        static color3 SLATEGRAY();
        static color3 SNOW();
        static color3 SPRINGGREEN();
        static color3 STEELBLUE();
        static color3 TAN();
        static color3 TEAL();
        static color3 THISTLE();
        static color3 TOMATO();
        static color3 TURQUOISE();
        static color3 VIOLET();
        static color3 WHEAT();
        static color3 WHITE();
        static color3 WHITESMOKE();
        static color3 YELLOW();
        static color3 YELLOWGREEN();
    };
}

#endif //RAYTRACER_COLOR3_H

#ifndef RAYTRACER_COLOR3_H
#define RAYTRACER_COLOR3_H

#include <ostream>

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

        static rt::color3 ALICEBLUE();
        static rt::color3 ANTIQUEWHITE();
        static rt::color3 AQUA();
        static rt::color3 AQUAMARINE();
        static rt::color3 AZURE();
        static rt::color3 BEIGE();
        static rt::color3 BISQUE();
        static rt::color3 BLACK();
        static rt::color3 BLANCHEDALMOND();
        static rt::color3 BLUE();
        static rt::color3 BLUEVIOLET();
        static rt::color3 BROWN();
        static rt::color3 BURLYWOOD();
        static rt::color3 CADETBLUE();
        static rt::color3 CHARTREUSE();
        static rt::color3 CHOCOLATE();
        static rt::color3 CORAL();
        static rt::color3 CORNFLOWERBLUE();
        static rt::color3 CORNSILK();
        static rt::color3 CRIMSON();
        static rt::color3 CYAN();
        static rt::color3 DARKBLUE();
        static rt::color3 DARKCYAN();
        static rt::color3 DARKGOLDENROD();
        static rt::color3 DARKGRAY();
        static rt::color3 DARKGREEN();
        static rt::color3 DARKKHAKI();
        static rt::color3 DARKMAGENTA();
        static rt::color3 DARKOLIVEGREEN();
        static rt::color3 DARKORANGE();
        static rt::color3 DARKORCHID();
        static rt::color3 DARKRED();
        static rt::color3 DARKSALMON();
        static rt::color3 DARKSEAGREEN();
        static rt::color3 DARKSLATEBLUE();
        static rt::color3 DARKSLATEGRAY();
        static rt::color3 DARKTURQUOISE();
        static rt::color3 DARKVIOLET();
        static rt::color3 DEEPPINK();
        static rt::color3 DEEPSKYBLUE();
        static rt::color3 DIMGRAY();
        static rt::color3 DODGERBLUE();
        static rt::color3 FIREBRICK();
        static rt::color3 FLORALWHITE();
        static rt::color3 FORESTGREEN();
        static rt::color3 FUCHSIA();
        static rt::color3 GAINSBORO();
        static rt::color3 GHOSTWHITE();
        static rt::color3 GOLD();
        static rt::color3 GOLDENROD();
        static rt::color3 GRAY();
        static rt::color3 GREEN();
        static rt::color3 GREENYELLOW();
        static rt::color3 HONEYDEW();
        static rt::color3 HOTPINK();
        static rt::color3 INDIANRED();
        static rt::color3 INDIGO();
        static rt::color3 IVORY();
        static rt::color3 KHAKI();
        static rt::color3 LAVENDER();
        static rt::color3 LAVENDERBLUSH();
        static rt::color3 LAWNGREEN();
        static rt::color3 LEMONCHIFFON();
        static rt::color3 LIGHTBLUE();
        static rt::color3 LIGHTCORAL();
        static rt::color3 LIGHTCYAN();
        static rt::color3 LIGHTGOLDENRODYELLOW();
        static rt::color3 LIGHTGRAY();
        static rt::color3 LIGHTGREEN();
        static rt::color3 LIGHTPINK();
        static rt::color3 LIGHTSALMON();
        static rt::color3 LIGHTSEAGREEN();
        static rt::color3 LIGHTSKYBLUE();
        static rt::color3 LIGHTSLATEGRAY();
        static rt::color3 LIGHTSTEELBLUE();
        static rt::color3 LIGHTYELLOW();
        static rt::color3 LIME();
        static rt::color3 LIMEGREEN();
        static rt::color3 LINEN();
        static rt::color3 MAGENTA();
        static rt::color3 MAROON();
        static rt::color3 MEDIUMAQUAMARINE();
        static rt::color3 MEDIUMBLUE();
        static rt::color3 MEDIUMORCHID();
        static rt::color3 MEDIUMPURPLE();
        static rt::color3 MEDIUMSEAGREEN();
        static rt::color3 MEDIUMSLATEBLUE();
        static rt::color3 MEDIUMSPRINGGREEN();
        static rt::color3 MEDIUMTURQUOISE();
        static rt::color3 MEDIUMVIOLETRED();
        static rt::color3 MIDNIGHTBLUE();
        static rt::color3 MINTCREAM();
        static rt::color3 MISTYROSE();
        static rt::color3 MOCCASIN();
        static rt::color3 NAVAJOWHITE();
        static rt::color3 NAVY();
        static rt::color3 OLDLACE();
        static rt::color3 OLIVE();
        static rt::color3 OLIVEDRAB();
        static rt::color3 ORANGE();
        static rt::color3 ORANGERED();
        static rt::color3 ORCHID();
        static rt::color3 PALEGOLDENROD();
        static rt::color3 PALEGREEN();
        static rt::color3 PALETURQUOISE();
        static rt::color3 PALEVIOLETRED();
        static rt::color3 PAPAYAWHIP();
        static rt::color3 PEACHPUFF();
        static rt::color3 PERU();
        static rt::color3 PINK();
        static rt::color3 PLUM();
        static rt::color3 POWDERBLUE();
        static rt::color3 PURPLE();
        static rt::color3 RED();
        static rt::color3 ROSYBROWN();
        static rt::color3 ROYALBLUE();
        static rt::color3 SADDLEBROWN();
        static rt::color3 SALMON();
        static rt::color3 SANDYBROWN();
        static rt::color3 SEAGREEN();
        static rt::color3 SEASHELL();
        static rt::color3 SIENNA();
        static rt::color3 SILVER();
        static rt::color3 SKYBLUE();
        static rt::color3 SLATEBLUE();
        static rt::color3 SLATEGRAY();
        static rt::color3 SNOW();
        static rt::color3 SPRINGGREEN();
        static rt::color3 STEELBLUE();
        static rt::color3 TAN();
        static rt::color3 TEAL();
        static rt::color3 THISTLE();
        static rt::color3 TOMATO();
        static rt::color3 TURQUOISE();
        static rt::color3 VIOLET();
        static rt::color3 WHEAT();
        static rt::color3 WHITE();
        static rt::color3 WHITESMOKE();
        static rt::color3 YELLOW();
        static rt::color3 YELLOWGREEN();
    };
}

#endif //RAYTRACER_COLOR3_H

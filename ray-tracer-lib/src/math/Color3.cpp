#include <cmath>
#include <rt/utils/StringUtils.h>
#include "rt/math/Color3.h"

namespace rt {
    Color3::Color3() : r(0), g(0), b(0) {}

    Color3::Color3(double gray) : r(gray), g(gray), b(gray) {}

    Color3::Color3(double r, double g, double b) : r(r), g(g), b(b) {}

    Color3::Color3(int r, int g, int b) : Color3(r / 255.0, g / 255.0, b / 255.0) {}

    Color3 &Color3::add(const Color3 &other) {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    Color3 &Color3::sub(const Color3 &other) {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        return *this;
    }

    Color3 &Color3::mul(double other) {
        r *= other;
        g *= other;
        b *= other;
        return *this;
    }

    Color3 &Color3::mul(const Color3 &other) {
        r *= other.r;
        g *= other.g;
        b *= other.b;
        return *this;
    }

    Color3 &Color3::div(double other) {
        r /= other;
        g /= other;
        b /= other;
        return *this;
    }

    Color3 operator+(Color3 left, const Color3 &right) {
        return left.add(right);
    }

    Color3 operator-(Color3 left, const Color3 &right) {
        return left.sub(right);
    }

    Color3 operator*(Color3 left, const Color3 &right) {
        return left.mul(right);
    }

    Color3 operator*(Color3 left, double right) {
        return left.mul(right);
    }

    Color3 operator/(Color3 left, double right) {
        return left.div(right);
    }

    Color3 &Color3::operator+=(const Color3 &other) {
        return add(other);
    }

    Color3 &Color3::operator-=(const Color3 &other) {
        return sub(other);
    }

    Color3 &Color3::operator*=(double other) {
        return mul(other);
    }

    Color3 &Color3::operator/=(double other) {
        return div(other);
    }

    bool Color3::operator==(const Color3 &other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    bool Color3::operator!=(const Color3 &other) const {
        return !(*this == other);
    }

    void Color3::print(std::ostream &stream, int indent) const {
        stream << two_spaces(indent) << "{" << std::endl
               << two_spaces(indent + 1) << "\"r\": " << r << "," << std::endl
               << two_spaces(indent + 1) << "\"g\": " << g << "," << std::endl
               << two_spaces(indent + 1) << "\"b\": " << b << std::endl
               << two_spaces(indent) << "}";
    }

    std::array<double, 3> Color3::hsb_to_rgb(double hue, double saturation, double brightness) {
        double normalized_hue = std::fmod(std::fmod(hue, 360) + 360, 360);
        hue = normalized_hue / 360;

        double r = 0, g = 0, b = 0;
        if (saturation == 0) {
            r = g = b = brightness;
        } else {
            double h = (hue - floor(hue)) * 6.0;
            double f = h - floor(h);
            double p = brightness * (1.0 - saturation);
            double q = brightness * (1.0 - saturation * f);
            double t = brightness * (1.0 - (saturation * (1.0 - f)));
            switch ((int) h) {
                case 0:
                    r = brightness;
                    g = t;
                    b = p;
                    break;
                case 1:
                    r = q;
                    g = brightness;
                    b = p;
                    break;
                case 2:
                    r = p;
                    g = brightness;
                    b = t;
                    break;
                case 3:
                    r = p;
                    g = q;
                    b = brightness;
                    break;
                case 4:
                    r = t;
                    g = p;
                    b = brightness;
                    break;
                case 5:
                    r = brightness;
                    g = p;
                    b = q;
                    break;
            }
        }
        return {r, g, b};
    }

    std::array<double, 3> Color3::rgb_to_hsv(double r, double g, double b) {
        double hue, saturation, brightness;
        double cmax = (r > g) ? r : g;
        if (b > cmax) cmax = b;
        double cmin = (r < g) ? r : g;
        if (b < cmin) cmin = b;

        brightness = cmax;
        if (cmax != 0)
            saturation = (double) (cmax - cmin) / cmax;
        else
            saturation = 0;

        if (saturation == 0) {
            hue = 0;
        } else {
            double redc = (cmax - r) / (cmax - cmin);
            double greenc = (cmax - g) / (cmax - cmin);
            double bluec = (cmax - b) / (cmax - cmin);
            if (r == cmax)
                hue = bluec - greenc;
            else if (g == cmax)
                hue = 2.0 + redc - bluec;
            else
                hue = 4.0 + greenc - redc;
            hue = hue / 6.0;
            if (hue < 0)
                hue = hue + 1.0;
        }
        return {hue * 360, saturation, brightness};
    }

    Color3 Color3::rgb(double r, double g, double b) {
        return Color3(r, g, b);
    }

    Color3 Color3::hsb(double h, double s, double b) {
        std::array<double, 3> rgb = hsb_to_rgb(h, s, b);
        return Color3(rgb[0], rgb[1], rgb[2]);
    }

    Color3 Color3::derive(double hue_shift, double saturation_factor, double brightness_factor) const {
        std::array<double, 3> hsb = Color3::rgb_to_hsv(r, g, b);

        double brightness = hsb[2];
        if (brightness == 0 && brightness_factor > 1.0) {
            brightness = 0.05;
        }

        double hue = std::fmod(std::fmod(hsb[0] + hue_shift, 360) + 360, 360);
        double saturation = fmax(fmin(hsb[1] * saturation_factor, 1.0), 0.0);
        brightness = fmax(fmin(brightness * brightness_factor, 1.0), 0.0);

        return Color3::hsb(hue, saturation, brightness);
    }

    Color3 Color3::darker() const {
        return derive(0, 1.0, DARKER_BRIGHTER_FACTOR);
    }

    Color3 Color3::brighter() const {
        return derive(0, 1.0, 1.0 / DARKER_BRIGHTER_FACTOR);
    }

    Color3 Color3::saturated() const {
        return derive(0, 1.0 / SATURATE_DESATURATE_FACTOR, 1.0);
    }

    Color3 Color3::desaturated() const {
        return derive(0, SATURATE_DESATURATE_FACTOR, 1.0);
    }

    Color3 Color3::grayscale() const {
        double gray = 0.299 * r + 0.587 * g + 0.114 * b;
        return Color3(gray);
    }

    Color3 Color3::inverted() const {
        return Color3(1.0 - r, 1.0 - g, 1.0 - b);
    }

    Color3 Color3::interpolated(const Color3 &other, double factor) const {
        return Color3(
                r + (other.r - r) * factor,
                g + (other.g - g) * factor,
                b + (other.b - b) * factor);
    }

    Color3 Color3::gamma_correction(double gamma) const {
        double exp = 1.0 / gamma;
        return Color3(
                pow(r, exp),
                pow(g, exp),
                pow(b, exp));
    }

    Color3 Color3::ALICEBLUE() {
        return Color3(0.9411765f, 0.972549f, 1.0f);
    }

    Color3 Color3::ANTIQUEWHITE() {
        return Color3(0.98039216f, 0.92156863f, 0.84313726f);
    }

    Color3 Color3::AQUA() {
        return Color3(0.0f, 1.0f, 1.0f);
    }

    Color3 Color3::AQUAMARINE() {
        return Color3(0.49803922f, 1.0f, 0.83137256f);
    }

    Color3 Color3::AZURE() {
        return Color3(0.9411765f, 1.0f, 1.0f);
    }

    Color3 Color3::BEIGE() {
        return Color3(0.9607843f, 0.9607843f, 0.8627451f);
    }

    Color3 Color3::BISQUE() {
        return Color3(1.0f, 0.89411765f, 0.76862746f);
    }

    Color3 Color3::BLACK() {
        return Color3(0.0f, 0.0f, 0.0f);
    }

    Color3 Color3::BLANCHEDALMOND() {
        return Color3(1.0f, 0.92156863f, 0.8039216f);
    }

    Color3 Color3::BLUE() {
        return Color3(0.0f, 0.0f, 1.0f);
    }

    Color3 Color3::BLUEVIOLET() {
        return Color3(0.5411765f, 0.16862746f, 0.8862745f);
    }

    Color3 Color3::BROWN() {
        return Color3(0.64705884f, 0.16470589f, 0.16470589f);
    }

    Color3 Color3::BURLYWOOD() {
        return Color3(0.87058824f, 0.72156864f, 0.5294118f);
    }

    Color3 Color3::CADETBLUE() {
        return Color3(0.37254903f, 0.61960787f, 0.627451f);
    }

    Color3 Color3::CHARTREUSE() {
        return Color3(0.49803922f, 1.0f, 0.0f);
    }

    Color3 Color3::CHOCOLATE() {
        return Color3(0.8235294f, 0.4117647f, 0.11764706f);
    }

    Color3 Color3::CORAL() {
        return Color3(1.0f, 0.49803922f, 0.3137255f);
    }

    Color3 Color3::CORNFLOWERBLUE() {
        return Color3(0.39215687f, 0.58431375f, 0.92941177f);
    }

    Color3 Color3::CORNSILK() {
        return Color3(1.0f, 0.972549f, 0.8627451f);
    }

    Color3 Color3::CRIMSON() {
        return Color3(0.8627451f, 0.078431375f, 0.23529412f);
    }

    Color3 Color3::CYAN() {
        return Color3(0.0f, 1.0f, 1.0f);
    }

    Color3 Color3::DARKBLUE() {
        return Color3(0.0f, 0.0f, 0.54509807f);
    }

    Color3 Color3::DARKCYAN() {
        return Color3(0.0f, 0.54509807f, 0.54509807f);
    }

    Color3 Color3::DARKGOLDENROD() {
        return Color3(0.72156864f, 0.5254902f, 0.043137256f);
    }

    Color3 Color3::DARKGRAY() {
        return Color3(0.6627451f, 0.6627451f, 0.6627451f);
    }

    Color3 Color3::DARKGREEN() {
        return Color3(0.0f, 0.39215687f, 0.0f);
    }

    Color3 Color3::DARKKHAKI() {
        return Color3(0.7411765f, 0.7176471f, 0.41960785f);
    }

    Color3 Color3::DARKMAGENTA() {
        return Color3(0.54509807f, 0.0f, 0.54509807f);
    }

    Color3 Color3::DARKOLIVEGREEN() {
        return Color3(0.33333334f, 0.41960785f, 0.18431373f);
    }

    Color3 Color3::DARKORANGE() {
        return Color3(1.0f, 0.54901963f, 0.0f);
    }

    Color3 Color3::DARKORCHID() {
        return Color3(0.6f, 0.19607843f, 0.8f);
    }

    Color3 Color3::DARKRED() {
        return Color3(0.54509807f, 0.0f, 0.0f);
    }

    Color3 Color3::DARKSALMON() {
        return Color3(0.9137255f, 0.5882353f, 0.47843137f);
    }

    Color3 Color3::DARKSEAGREEN() {
        return Color3(0.56078434f, 0.7372549f, 0.56078434f);
    }

    Color3 Color3::DARKSLATEBLUE() {
        return Color3(0.28235295f, 0.23921569f, 0.54509807f);
    }

    Color3 Color3::DARKSLATEGRAY() {
        return Color3(0.18431373f, 0.30980393f, 0.30980393f);
    }

    Color3 Color3::DARKTURQUOISE() {
        return Color3(0.0f, 0.80784315f, 0.81960785f);
    }

    Color3 Color3::DARKVIOLET() {
        return Color3(0.5803922f, 0.0f, 0.827451f);
    }

    Color3 Color3::DEEPPINK() {
        return Color3(1.0f, 0.078431375f, 0.5764706f);
    }

    Color3 Color3::DEEPSKYBLUE() {
        return Color3(0.0f, 0.7490196f, 1.0f);
    }

    Color3 Color3::DIMGRAY() {
        return Color3(0.4117647f, 0.4117647f, 0.4117647f);
    }

    Color3 Color3::DODGERBLUE() {
        return Color3(0.11764706f, 0.5647059f, 1.0f);
    }

    Color3 Color3::FIREBRICK() {
        return Color3(0.69803923f, 0.13333334f, 0.13333334f);
    }

    Color3 Color3::FLORALWHITE() {
        return Color3(1.0f, 0.98039216f, 0.9411765f);
    }

    Color3 Color3::FORESTGREEN() {
        return Color3(0.13333334f, 0.54509807f, 0.13333334f);
    }

    Color3 Color3::FUCHSIA() {
        return Color3(1.0f, 0.0f, 1.0f);
    }

    Color3 Color3::GAINSBORO() {
        return Color3(0.8627451f, 0.8627451f, 0.8627451f);
    }

    Color3 Color3::GHOSTWHITE() {
        return Color3(0.972549f, 0.972549f, 1.0f);
    }

    Color3 Color3::GOLD() {
        return Color3(1.0f, 0.84313726f, 0.0f);
    }

    Color3 Color3::GOLDENROD() {
        return Color3(0.85490197f, 0.64705884f, 0.1254902f);
    }

    Color3 Color3::GRAY() {
        return Color3(0.5019608f, 0.5019608f, 0.5019608f);
    }

    Color3 Color3::GREEN() {
        return Color3(0.0f, 0.5019608f, 0.0f);
    }

    Color3 Color3::GREENYELLOW() {
        return Color3(0.6784314f, 1.0f, 0.18431373f);
    }

    Color3 Color3::HONEYDEW() {
        return Color3(0.9411765f, 1.0f, 0.9411765f);
    }

    Color3 Color3::HOTPINK() {
        return Color3(1.0f, 0.4117647f, 0.7058824f);
    }

    Color3 Color3::INDIANRED() {
        return Color3(0.8039216f, 0.36078432f, 0.36078432f);
    }

    Color3 Color3::INDIGO() {
        return Color3(0.29411766f, 0.0f, 0.50980395f);
    }

    Color3 Color3::IVORY() {
        return Color3(1.0f, 1.0f, 0.9411765f);
    }

    Color3 Color3::KHAKI() {
        return Color3(0.9411765f, 0.9019608f, 0.54901963f);
    }

    Color3 Color3::LAVENDER() {
        return Color3(0.9019608f, 0.9019608f, 0.98039216f);
    }

    Color3 Color3::LAVENDERBLUSH() {
        return Color3(1.0f, 0.9411765f, 0.9607843f);
    }

    Color3 Color3::LAWNGREEN() {
        return Color3(0.4862745f, 0.9882353f, 0.0f);
    }

    Color3 Color3::LEMONCHIFFON() {
        return Color3(1.0f, 0.98039216f, 0.8039216f);
    }

    Color3 Color3::LIGHTBLUE() {
        return Color3(0.6784314f, 0.84705883f, 0.9019608f);
    }

    Color3 Color3::LIGHTCORAL() {
        return Color3(0.9411765f, 0.5019608f, 0.5019608f);
    }

    Color3 Color3::LIGHTCYAN() {
        return Color3(0.8784314f, 1.0f, 1.0f);
    }

    Color3 Color3::LIGHTGOLDENRODYELLOW() {
        return Color3(0.98039216f, 0.98039216f, 0.8235294f);
    }

    Color3 Color3::LIGHTGRAY() {
        return Color3(0.827451f, 0.827451f, 0.827451f);
    }

    Color3 Color3::LIGHTGREEN() {
        return Color3(0.5647059f, 0.93333334f, 0.5647059f);
    }

    Color3 Color3::LIGHTPINK() {
        return Color3(1.0f, 0.7137255f, 0.75686276f);
    }

    Color3 Color3::LIGHTSALMON() {
        return Color3(1.0f, 0.627451f, 0.47843137f);
    }

    Color3 Color3::LIGHTSEAGREEN() {
        return Color3(0.1254902f, 0.69803923f, 0.6666667f);
    }

    Color3 Color3::LIGHTSKYBLUE() {
        return Color3(0.5294118f, 0.80784315f, 0.98039216f);
    }

    Color3 Color3::LIGHTSLATEGRAY() {
        return Color3(0.46666667f, 0.53333336f, 0.6f);
    }

    Color3 Color3::LIGHTSTEELBLUE() {
        return Color3(0.6901961f, 0.76862746f, 0.87058824f);
    }

    Color3 Color3::LIGHTYELLOW() {
        return Color3(1.0f, 1.0f, 0.8784314f);
    }

    Color3 Color3::LIME() {
        return Color3(0.0f, 1.0f, 0.0f);
    }

    Color3 Color3::LIMEGREEN() {
        return Color3(0.19607843f, 0.8039216f, 0.19607843f);
    }

    Color3 Color3::LINEN() {
        return Color3(0.98039216f, 0.9411765f, 0.9019608f);
    }

    Color3 Color3::MAGENTA() {
        return Color3(1.0f, 0.0f, 1.0f);
    }

    Color3 Color3::MAROON() {
        return Color3(0.5019608f, 0.0f, 0.0f);
    }

    Color3 Color3::MEDIUMAQUAMARINE() {
        return Color3(0.4f, 0.8039216f, 0.6666667f);
    }

    Color3 Color3::MEDIUMBLUE() {
        return Color3(0.0f, 0.0f, 0.8039216f);
    }

    Color3 Color3::MEDIUMORCHID() {
        return Color3(0.7294118f, 0.33333334f, 0.827451f);
    }

    Color3 Color3::MEDIUMPURPLE() {
        return Color3(0.5764706f, 0.4392157f, 0.85882354f);
    }

    Color3 Color3::MEDIUMSEAGREEN() {
        return Color3(0.23529412f, 0.7019608f, 0.44313726f);
    }

    Color3 Color3::MEDIUMSLATEBLUE() {
        return Color3(0.48235294f, 0.40784314f, 0.93333334f);
    }

    Color3 Color3::MEDIUMSPRINGGREEN() {
        return Color3(0.0f, 0.98039216f, 0.6039216f);
    }

    Color3 Color3::MEDIUMTURQUOISE() {
        return Color3(0.28235295f, 0.81960785f, 0.8f);
    }

    Color3 Color3::MEDIUMVIOLETRED() {
        return Color3(0.78039217f, 0.08235294f, 0.52156866f);
    }

    Color3 Color3::MIDNIGHTBLUE() {
        return Color3(0.09803922f, 0.09803922f, 0.4392157f);
    }

    Color3 Color3::MINTCREAM() {
        return Color3(0.9607843f, 1.0f, 0.98039216f);
    }

    Color3 Color3::MISTYROSE() {
        return Color3(1.0f, 0.89411765f, 0.88235295f);
    }

    Color3 Color3::MOCCASIN() {
        return Color3(1.0f, 0.89411765f, 0.70980394f);
    }

    Color3 Color3::NAVAJOWHITE() {
        return Color3(1.0f, 0.87058824f, 0.6784314f);
    }

    Color3 Color3::NAVY() {
        return Color3(0.0f, 0.0f, 0.5019608f);
    }

    Color3 Color3::OLDLACE() {
        return Color3(0.99215686f, 0.9607843f, 0.9019608f);
    }

    Color3 Color3::OLIVE() {
        return Color3(0.5019608f, 0.5019608f, 0.0f);
    }

    Color3 Color3::OLIVEDRAB() {
        return Color3(0.41960785f, 0.5568628f, 0.13725491f);
    }

    Color3 Color3::ORANGE() {
        return Color3(1.0f, 0.64705884f, 0.0f);
    }

    Color3 Color3::ORANGERED() {
        return Color3(1.0f, 0.27058825f, 0.0f);
    }

    Color3 Color3::ORCHID() {
        return Color3(0.85490197f, 0.4392157f, 0.8392157f);
    }

    Color3 Color3::PALEGOLDENROD() {
        return Color3(0.93333334f, 0.9098039f, 0.6666667f);
    }

    Color3 Color3::PALEGREEN() {
        return Color3(0.59607846f, 0.9843137f, 0.59607846f);
    }

    Color3 Color3::PALETURQUOISE() {
        return Color3(0.6862745f, 0.93333334f, 0.93333334f);
    }

    Color3 Color3::PALEVIOLETRED() {
        return Color3(0.85882354f, 0.4392157f, 0.5764706f);
    }

    Color3 Color3::PAPAYAWHIP() {
        return Color3(1.0f, 0.9372549f, 0.8352941f);
    }

    Color3 Color3::PEACHPUFF() {
        return Color3(1.0f, 0.85490197f, 0.7254902f);
    }

    Color3 Color3::PERU() {
        return Color3(0.8039216f, 0.52156866f, 0.24705882f);
    }

    Color3 Color3::PINK() {
        return Color3(1.0f, 0.7529412f, 0.79607844f);
    }

    Color3 Color3::PLUM() {
        return Color3(0.8666667f, 0.627451f, 0.8666667f);
    }

    Color3 Color3::POWDERBLUE() {
        return Color3(0.6901961f, 0.8784314f, 0.9019608f);
    }

    Color3 Color3::PURPLE() {
        return Color3(0.5019608f, 0.0f, 0.5019608f);
    }

    Color3 Color3::RED() {
        return Color3(1.0f, 0.0f, 0.0f);
    }

    Color3 Color3::ROSYBROWN() {
        return Color3(0.7372549f, 0.56078434f, 0.56078434f);
    }

    Color3 Color3::ROYALBLUE() {
        return Color3(0.25490198f, 0.4117647f, 0.88235295f);
    }

    Color3 Color3::SADDLEBROWN() {
        return Color3(0.54509807f, 0.27058825f, 0.07450981f);
    }

    Color3 Color3::SALMON() {
        return Color3(0.98039216f, 0.5019608f, 0.44705883f);
    }

    Color3 Color3::SANDYBROWN() {
        return Color3(0.95686275f, 0.6431373f, 0.3764706f);
    }

    Color3 Color3::SEAGREEN() {
        return Color3(0.18039216f, 0.54509807f, 0.34117648f);
    }

    Color3 Color3::SEASHELL() {
        return Color3(1.0f, 0.9607843f, 0.93333334f);
    }

    Color3 Color3::SIENNA() {
        return Color3(0.627451f, 0.32156864f, 0.1764706f);
    }

    Color3 Color3::SILVER() {
        return Color3(0.7529412f, 0.7529412f, 0.7529412f);
    }

    Color3 Color3::SKYBLUE() {
        return Color3(0.5294118f, 0.80784315f, 0.92156863f);
    }

    Color3 Color3::SLATEBLUE() {
        return Color3(0.41568628f, 0.3529412f, 0.8039216f);
    }

    Color3 Color3::SLATEGRAY() {
        return Color3(0.4392157f, 0.5019608f, 0.5647059f);
    }

    Color3 Color3::SNOW() {
        return Color3(1.0f, 0.98039216f, 0.98039216f);
    }

    Color3 Color3::SPRINGGREEN() {
        return Color3(0.0f, 1.0f, 0.49803922f);
    }

    Color3 Color3::STEELBLUE() {
        return Color3(0.27450982f, 0.50980395f, 0.7058824f);
    }

    Color3 Color3::TAN() {
        return Color3(0.8235294f, 0.7058824f, 0.54901963f);
    }

    Color3 Color3::TEAL() {
        return Color3(0.0f, 0.5019608f, 0.5019608f);
    }

    Color3 Color3::THISTLE() {
        return Color3(0.84705883f, 0.7490196f, 0.84705883f);
    }

    Color3 Color3::TOMATO() {
        return Color3(1.0f, 0.3882353f, 0.2784314f);
    }

    Color3 Color3::TURQUOISE() {
        return Color3(0.2509804f, 0.8784314f, 0.8156863f);
    }

    Color3 Color3::VIOLET() {
        return Color3(0.93333334f, 0.50980395f, 0.93333334f);
    }

    Color3 Color3::WHEAT() {
        return Color3(0.9607843f, 0.87058824f, 0.7019608f);
    }

    Color3 Color3::WHITE() {
        return Color3(1.0f, 1.0f, 1.0f);
    }

    Color3 Color3::WHITESMOKE() {
        return Color3(0.9607843f, 0.9607843f, 0.9607843f);
    }

    Color3 Color3::YELLOW() {
        return Color3(1.0f, 1.0f, 0.0f);
    }

    Color3 Color3::YELLOWGREEN() {
        return Color3(0.6039216f, 0.8039216f, 0.19607843f);
    }
}

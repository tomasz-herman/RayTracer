#include <cmath>
#include "rt/math/color3.h"

namespace rt {
    color3::color3() : r(0), g(0), b(0) {}
    color3::color3(double gray) : r(gray), g(gray), b(gray) {}
    color3::color3(double r, double g, double b) : r(r), g(g), b(b) {}
    color3::color3(int r, int g, int b) : color3(r / 255.0, g / 255.0, b / 255.0) {}

    color3 &color3::add(const color3 &other) {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }

    color3 &color3::sub(const color3 &other) {
        r -= other.r;
        g -= other.g;
        b -= other.b;
        return *this;
    }

    color3 &color3::mul(double other) {
        r *= other;
        g *= other;
        b *= other;
        return *this;
    }

    color3 &color3::div(double other) {
        r /= other;
        g /= other;
        b /= other;
        return *this;
    }

    color3 operator+(color3 left, const color3 &right) {
        return left.add(right);
    }

    color3 operator-(color3 left, const color3 &right) {
        return left.sub(right);
    }

    color3 operator*(color3 left, double right) {
        return left.mul(right);
    }

    color3 operator/(color3 left, double right) {
        return left.div(right);
    }

    color3 &color3::operator+=(const color3 &other) {
        return add(other);
    }

    color3 &color3::operator-=(const color3 &other) {
        return sub(other);
    }

    color3 &color3::operator*=(float other) {
        return mul(other);
    }

    color3 &color3::operator/=(float other) {
        return div(other);
    }

    bool color3::operator==(const color3 &other) const {
        return r == other.r && g == other.g && b == other.b;
    }

    bool color3::operator!=(const color3 &other) const {
        return !(*this == other);
    }

    std::ostream &operator<<(std::ostream &stream, const color3 &color3) {
        stream << "(r:" << color3.r << ", g:" << color3.g << ", b:" << color3.b << ")";
        return stream;
    }

    std::array<double, 3> color3::hsb_to_rgb(double hue, double saturation, double brightness) {
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

    std::array<double, 3> color3::rgb_to_hsv(double r, double g, double b) {
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

    color3 color3::rgb(double r, double g, double b) {
        return color3(r, g, b);
    }

    color3 color3::hsb(double h, double s, double b) {
        std::array<double, 3> rgb = hsb_to_rgb(h, s, b);
        return color3(rgb[0], rgb[1], rgb[2]);
    }

    color3 color3::derive(double hue_shift, double saturation_factor, double brightness_factor) const {
        std::array<double, 3> hsb = color3::rgb_to_hsv(r, g, b);

        double brightness = hsb[2];
        if (brightness == 0 && brightness_factor > 1.0) {
            brightness = 0.05;
        }

        double hue = std::fmod(std::fmod(hsb[0] + hue_shift, 360) + 360, 360);
        double saturation = fmax(fmin(hsb[1] * saturation_factor, 1.0), 0.0);
        brightness = fmax(fmin(brightness * brightness_factor, 1.0), 0.0);

        return color3::hsb(hue, saturation, brightness);
    }

    color3 color3::darker() const {
        return derive(0, 1.0, DARKER_BRIGHTER_FACTOR);
    }

    color3 color3::brighter() const {
        return derive(0, 1.0, 1.0 / DARKER_BRIGHTER_FACTOR);
    }

    color3 color3::saturated() const {
        return derive(0, 1.0 / SATURATE_DESATURATE_FACTOR, 1.0);
    }

    color3 color3::desaturated() const {
        return derive(0, SATURATE_DESATURATE_FACTOR, 1.0);
    }

    color3 color3::grayscale() const {
        double gray = 0.299 * r + 0.587 * g + 0.114 * b;
        return color3(gray);
    }

    color3 color3::inverted() const {
        return color3(1.0 - r, 1.0 - g, 1.0 - b);
    }

    color3 color3::interpolated(const color3 &other, double factor) const {
        return color3(
                r + (other.r - r) * factor,
                g + (other.g - g) * factor,
                b + (other.b - b) * factor);
    }

    color3 color3::gamma_correction(double gamma) const {
        double exp = 1.0 / gamma;
        return color3(
                pow(r, exp),
                pow(g, exp),
                pow(b, exp));
    }

    color3 color3::ALICEBLUE() {
        return color3(0.9411765f, 0.972549f, 1.0f);
    }

    color3 color3::ANTIQUEWHITE() {
        return color3(0.98039216f, 0.92156863f, 0.84313726f);
    }

    color3 color3::AQUA() {
        return color3(0.0f, 1.0f, 1.0f);
    }

    color3 color3::AQUAMARINE() {
        return color3(0.49803922f, 1.0f, 0.83137256f);
    }

    color3 color3::AZURE() {
        return color3(0.9411765f, 1.0f, 1.0f);
    }

    color3 color3::BEIGE() {
        return color3(0.9607843f, 0.9607843f, 0.8627451f);
    }

    color3 color3::BISQUE() {
        return color3(1.0f, 0.89411765f, 0.76862746f);
    }

    color3 color3::BLACK() {
        return color3(0.0f, 0.0f, 0.0f);
    }

    color3 color3::BLANCHEDALMOND() {
        return color3(1.0f, 0.92156863f, 0.8039216f);
    }

    color3 color3::BLUE() {
        return color3(0.0f, 0.0f, 1.0f);
    }

    color3 color3::BLUEVIOLET() {
        return color3(0.5411765f, 0.16862746f, 0.8862745f);
    }

    color3 color3::BROWN() {
        return color3(0.64705884f, 0.16470589f, 0.16470589f);
    }

    color3 color3::BURLYWOOD() {
        return color3(0.87058824f, 0.72156864f, 0.5294118f);
    }

    color3 color3::CADETBLUE() {
        return color3(0.37254903f, 0.61960787f, 0.627451f);
    }

    color3 color3::CHARTREUSE() {
        return color3(0.49803922f, 1.0f, 0.0f);
    }

    color3 color3::CHOCOLATE() {
        return color3(0.8235294f, 0.4117647f, 0.11764706f);
    }

    color3 color3::CORAL() {
        return color3(1.0f, 0.49803922f, 0.3137255f);
    }

    color3 color3::CORNFLOWERBLUE() {
        return color3(0.39215687f, 0.58431375f, 0.92941177f);
    }

    color3 color3::CORNSILK() {
        return color3(1.0f, 0.972549f, 0.8627451f);
    }

    color3 color3::CRIMSON() {
        return color3(0.8627451f, 0.078431375f, 0.23529412f);
    }

    color3 color3::CYAN() {
        return color3(0.0f, 1.0f, 1.0f);
    }

    color3 color3::DARKBLUE() {
        return color3(0.0f, 0.0f, 0.54509807f);
    }

    color3 color3::DARKCYAN() {
        return color3(0.0f, 0.54509807f, 0.54509807f);
    }

    color3 color3::DARKGOLDENROD() {
        return color3(0.72156864f, 0.5254902f, 0.043137256f);
    }

    color3 color3::DARKGRAY() {
        return color3(0.6627451f, 0.6627451f, 0.6627451f);
    }

    color3 color3::DARKGREEN() {
        return color3(0.0f, 0.39215687f, 0.0f);
    }

    color3 color3::DARKKHAKI() {
        return color3(0.7411765f, 0.7176471f, 0.41960785f);
    }

    color3 color3::DARKMAGENTA() {
        return color3(0.54509807f, 0.0f, 0.54509807f);
    }

    color3 color3::DARKOLIVEGREEN() {
        return color3(0.33333334f, 0.41960785f, 0.18431373f);
    }

    color3 color3::DARKORANGE() {
        return color3(1.0f, 0.54901963f, 0.0f);
    }

    color3 color3::DARKORCHID() {
        return color3(0.6f, 0.19607843f, 0.8f);
    }

    color3 color3::DARKRED() {
        return color3(0.54509807f, 0.0f, 0.0f);
    }

    color3 color3::DARKSALMON() {
        return color3(0.9137255f, 0.5882353f, 0.47843137f);
    }

    color3 color3::DARKSEAGREEN() {
        return color3(0.56078434f, 0.7372549f, 0.56078434f);
    }

    color3 color3::DARKSLATEBLUE() {
        return color3(0.28235295f, 0.23921569f, 0.54509807f);
    }

    color3 color3::DARKSLATEGRAY() {
        return color3(0.18431373f, 0.30980393f, 0.30980393f);
    }

    color3 color3::DARKTURQUOISE() {
        return color3(0.0f, 0.80784315f, 0.81960785f);
    }

    color3 color3::DARKVIOLET() {
        return color3(0.5803922f, 0.0f, 0.827451f);
    }

    color3 color3::DEEPPINK() {
        return color3(1.0f, 0.078431375f, 0.5764706f);
    }

    color3 color3::DEEPSKYBLUE() {
        return color3(0.0f, 0.7490196f, 1.0f);
    }

    color3 color3::DIMGRAY() {
        return color3(0.4117647f, 0.4117647f, 0.4117647f);
    }

    color3 color3::DODGERBLUE() {
        return color3(0.11764706f, 0.5647059f, 1.0f);
    }

    color3 color3::FIREBRICK() {
        return color3(0.69803923f, 0.13333334f, 0.13333334f);
    }

    color3 color3::FLORALWHITE() {
        return color3(1.0f, 0.98039216f, 0.9411765f);
    }

    color3 color3::FORESTGREEN() {
        return color3(0.13333334f, 0.54509807f, 0.13333334f);
    }

    color3 color3::FUCHSIA() {
        return color3(1.0f, 0.0f, 1.0f);
    }

    color3 color3::GAINSBORO() {
        return color3(0.8627451f, 0.8627451f, 0.8627451f);
    }

    color3 color3::GHOSTWHITE() {
        return color3(0.972549f, 0.972549f, 1.0f);
    }

    color3 color3::GOLD() {
        return color3(1.0f, 0.84313726f, 0.0f);
    }

    color3 color3::GOLDENROD() {
        return color3(0.85490197f, 0.64705884f, 0.1254902f);
    }

    color3 color3::GRAY() {
        return color3(0.5019608f, 0.5019608f, 0.5019608f);
    }

    color3 color3::GREEN() {
        return color3(0.0f, 0.5019608f, 0.0f);
    }

    color3 color3::GREENYELLOW() {
        return color3(0.6784314f, 1.0f, 0.18431373f);
    }

    color3 color3::HONEYDEW() {
        return color3(0.9411765f, 1.0f, 0.9411765f);
    }

    color3 color3::HOTPINK() {
        return color3(1.0f, 0.4117647f, 0.7058824f);
    }

    color3 color3::INDIANRED() {
        return color3(0.8039216f, 0.36078432f, 0.36078432f);
    }

    color3 color3::INDIGO() {
        return color3(0.29411766f, 0.0f, 0.50980395f);
    }

    color3 color3::IVORY() {
        return color3(1.0f, 1.0f, 0.9411765f);
    }

    color3 color3::KHAKI() {
        return color3(0.9411765f, 0.9019608f, 0.54901963f);
    }

    color3 color3::LAVENDER() {
        return color3(0.9019608f, 0.9019608f, 0.98039216f);
    }

    color3 color3::LAVENDERBLUSH() {
        return color3(1.0f, 0.9411765f, 0.9607843f);
    }

    color3 color3::LAWNGREEN() {
        return color3(0.4862745f, 0.9882353f, 0.0f);
    }

    color3 color3::LEMONCHIFFON() {
        return color3(1.0f, 0.98039216f, 0.8039216f);
    }

    color3 color3::LIGHTBLUE() {
        return color3(0.6784314f, 0.84705883f, 0.9019608f);
    }

    color3 color3::LIGHTCORAL() {
        return color3(0.9411765f, 0.5019608f, 0.5019608f);
    }

    color3 color3::LIGHTCYAN() {
        return color3(0.8784314f, 1.0f, 1.0f);
    }

    color3 color3::LIGHTGOLDENRODYELLOW() {
        return color3(0.98039216f, 0.98039216f, 0.8235294f);
    }

    color3 color3::LIGHTGRAY() {
        return color3(0.827451f, 0.827451f, 0.827451f);
    }

    color3 color3::LIGHTGREEN() {
        return color3(0.5647059f, 0.93333334f, 0.5647059f);
    }

    color3 color3::LIGHTPINK() {
        return color3(1.0f, 0.7137255f, 0.75686276f);
    }

    color3 color3::LIGHTSALMON() {
        return color3(1.0f, 0.627451f, 0.47843137f);
    }

    color3 color3::LIGHTSEAGREEN() {
        return color3(0.1254902f, 0.69803923f, 0.6666667f);
    }

    color3 color3::LIGHTSKYBLUE() {
        return color3(0.5294118f, 0.80784315f, 0.98039216f);
    }

    color3 color3::LIGHTSLATEGRAY() {
        return color3(0.46666667f, 0.53333336f, 0.6f);
    }

    color3 color3::LIGHTSTEELBLUE() {
        return color3(0.6901961f, 0.76862746f, 0.87058824f);
    }

    color3 color3::LIGHTYELLOW() {
        return color3(1.0f, 1.0f, 0.8784314f);
    }

    color3 color3::LIME() {
        return color3(0.0f, 1.0f, 0.0f);
    }

    color3 color3::LIMEGREEN() {
        return color3(0.19607843f, 0.8039216f, 0.19607843f);
    }

    color3 color3::LINEN() {
        return color3(0.98039216f, 0.9411765f, 0.9019608f);
    }

    color3 color3::MAGENTA() {
        return color3(1.0f, 0.0f, 1.0f);
    }

    color3 color3::MAROON() {
        return color3(0.5019608f, 0.0f, 0.0f);
    }

    color3 color3::MEDIUMAQUAMARINE() {
        return color3(0.4f, 0.8039216f, 0.6666667f);
    }

    color3 color3::MEDIUMBLUE() {
        return color3(0.0f, 0.0f, 0.8039216f);
    }

    color3 color3::MEDIUMORCHID() {
        return color3(0.7294118f, 0.33333334f, 0.827451f);
    }

    color3 color3::MEDIUMPURPLE() {
        return color3(0.5764706f, 0.4392157f, 0.85882354f);
    }

    color3 color3::MEDIUMSEAGREEN() {
        return color3(0.23529412f, 0.7019608f, 0.44313726f);
    }

    color3 color3::MEDIUMSLATEBLUE() {
        return color3(0.48235294f, 0.40784314f, 0.93333334f);
    }

    color3 color3::MEDIUMSPRINGGREEN() {
        return color3(0.0f, 0.98039216f, 0.6039216f);
    }

    color3 color3::MEDIUMTURQUOISE() {
        return color3(0.28235295f, 0.81960785f, 0.8f);
    }

    color3 color3::MEDIUMVIOLETRED() {
        return color3(0.78039217f, 0.08235294f, 0.52156866f);
    }

    color3 color3::MIDNIGHTBLUE() {
        return color3(0.09803922f, 0.09803922f, 0.4392157f);
    }

    color3 color3::MINTCREAM() {
        return color3(0.9607843f, 1.0f, 0.98039216f);
    }

    color3 color3::MISTYROSE() {
        return color3(1.0f, 0.89411765f, 0.88235295f);
    }

    color3 color3::MOCCASIN() {
        return color3(1.0f, 0.89411765f, 0.70980394f);
    }

    color3 color3::NAVAJOWHITE() {
        return color3(1.0f, 0.87058824f, 0.6784314f);
    }

    color3 color3::NAVY() {
        return color3(0.0f, 0.0f, 0.5019608f);
    }

    color3 color3::OLDLACE() {
        return color3(0.99215686f, 0.9607843f, 0.9019608f);
    }

    color3 color3::OLIVE() {
        return color3(0.5019608f, 0.5019608f, 0.0f);
    }

    color3 color3::OLIVEDRAB() {
        return color3(0.41960785f, 0.5568628f, 0.13725491f);
    }

    color3 color3::ORANGE() {
        return color3(1.0f, 0.64705884f, 0.0f);
    }

    color3 color3::ORANGERED() {
        return color3(1.0f, 0.27058825f, 0.0f);
    }

    color3 color3::ORCHID() {
        return color3(0.85490197f, 0.4392157f, 0.8392157f);
    }

    color3 color3::PALEGOLDENROD() {
        return color3(0.93333334f, 0.9098039f, 0.6666667f);
    }

    color3 color3::PALEGREEN() {
        return color3(0.59607846f, 0.9843137f, 0.59607846f);
    }

    color3 color3::PALETURQUOISE() {
        return color3(0.6862745f, 0.93333334f, 0.93333334f);
    }

    color3 color3::PALEVIOLETRED() {
        return color3(0.85882354f, 0.4392157f, 0.5764706f);
    }

    color3 color3::PAPAYAWHIP() {
        return color3(1.0f, 0.9372549f, 0.8352941f);
    }

    color3 color3::PEACHPUFF() {
        return color3(1.0f, 0.85490197f, 0.7254902f);
    }

    color3 color3::PERU() {
        return color3(0.8039216f, 0.52156866f, 0.24705882f);
    }

    color3 color3::PINK() {
        return color3(1.0f, 0.7529412f, 0.79607844f);
    }

    color3 color3::PLUM() {
        return color3(0.8666667f, 0.627451f, 0.8666667f);
    }

    color3 color3::POWDERBLUE() {
        return color3(0.6901961f, 0.8784314f, 0.9019608f);
    }

    color3 color3::PURPLE() {
        return color3(0.5019608f, 0.0f, 0.5019608f);
    }

    color3 color3::RED() {
        return color3(1.0f, 0.0f, 0.0f);
    }

    color3 color3::ROSYBROWN() {
        return color3(0.7372549f, 0.56078434f, 0.56078434f);
    }

    color3 color3::ROYALBLUE() {
        return color3(0.25490198f, 0.4117647f, 0.88235295f);
    }

    color3 color3::SADDLEBROWN() {
        return color3(0.54509807f, 0.27058825f, 0.07450981f);
    }

    color3 color3::SALMON() {
        return color3(0.98039216f, 0.5019608f, 0.44705883f);
    }

    color3 color3::SANDYBROWN() {
        return color3(0.95686275f, 0.6431373f, 0.3764706f);
    }

    color3 color3::SEAGREEN() {
        return color3(0.18039216f, 0.54509807f, 0.34117648f);
    }

    color3 color3::SEASHELL() {
        return color3(1.0f, 0.9607843f, 0.93333334f);
    }

    color3 color3::SIENNA() {
        return color3(0.627451f, 0.32156864f, 0.1764706f);
    }

    color3 color3::SILVER() {
        return color3(0.7529412f, 0.7529412f, 0.7529412f);
    }

    color3 color3::SKYBLUE() {
        return color3(0.5294118f, 0.80784315f, 0.92156863f);
    }

    color3 color3::SLATEBLUE() {
        return color3(0.41568628f, 0.3529412f, 0.8039216f);
    }

    color3 color3::SLATEGRAY() {
        return color3(0.4392157f, 0.5019608f, 0.5647059f);
    }

    color3 color3::SNOW() {
        return color3(1.0f, 0.98039216f, 0.98039216f);
    }

    color3 color3::SPRINGGREEN() {
        return color3(0.0f, 1.0f, 0.49803922f);
    }

    color3 color3::STEELBLUE() {
        return color3(0.27450982f, 0.50980395f, 0.7058824f);
    }

    color3 color3::TAN() {
        return color3(0.8235294f, 0.7058824f, 0.54901963f);
    }

    color3 color3::TEAL() {
        return color3(0.0f, 0.5019608f, 0.5019608f);
    }

    color3 color3::THISTLE() {
        return color3(0.84705883f, 0.7490196f, 0.84705883f);
    }

    color3 color3::TOMATO() {
        return color3(1.0f, 0.3882353f, 0.2784314f);
    }

    color3 color3::TURQUOISE() {
        return color3(0.2509804f, 0.8784314f, 0.8156863f);
    }

    color3 color3::VIOLET() {
        return color3(0.93333334f, 0.50980395f, 0.93333334f);
    }

    color3 color3::WHEAT() {
        return color3(0.9607843f, 0.87058824f, 0.7019608f);
    }

    color3 color3::WHITE() {
        return color3(1.0f, 1.0f, 1.0f);
    }

    color3 color3::WHITESMOKE() {
        return color3(0.9607843f, 0.9607843f, 0.9607843f);
    }

    color3 color3::YELLOW() {
        return color3(1.0f, 1.0f, 0.0f);
    }

    color3 color3::YELLOWGREEN() {
        return color3(0.6039216f, 0.8039216f, 0.19607843f);
    }
}

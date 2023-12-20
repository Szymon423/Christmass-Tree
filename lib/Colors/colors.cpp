#include "colors.hpp"
#include "modes.hpp"
#include "Arduino.h"
#include "utilities.hpp"
#include "extern.hpp"

Color::Color()
{
    r = 255.0f;
    g = 255.0f;
    b = 255.0f;
}

Color::Color(float RGB)
{
    RGB = ConstrainTo(RGB, 0.0f,  255.0f);
    r = RGB;
    g = RGB;
    b = RGB;
    CartesianToSpherical(r, g, b, radius, theta, fi);
}

Color::Color(float R, float G, float B)
{
    r = ConstrainTo(R, 0.0f,  255.0f);
    g = ConstrainTo(G, 0.0f,  255.0f);
    b = ConstrainTo(B, 0.0f,  255.0f);
    CartesianToSpherical(r, g, b, radius, theta, fi);
}

uint8_t Color::R() const
{
    return r > 255.0f ? 255 : (char)r;
}

uint8_t Color::G() const
{
    return g > 255.0f ? 255 : (char)g;
}

uint8_t Color::B() const
{
    return b > 255.0f ? 255 : (char)b;
}

void CartesianToSpherical(float R, float G, float B, float& radius, float& theta, float& fi)
{
    radius = sqrtf(powf(R, 2.0f) + powf(G, 2.0f) + powf(B, 2.0f));
    fi = atan2(G, R);
    theta = asinf(B / radius);
}

void SphericalToCartesian(float radius, float theta, float fi, float& R, float& G, float& B)
{
    R = radius * cosf(theta) * cosf(fi);
    G = radius * cosf(theta) * sinf(fi);
    B = radius * sinf(theta);
}

Color GetColor(ColorMode colorMode)
{
    if (powerMode == PowerMode::OFF) return Color(0);

    int maxBrightness = GetMaxBrightness();
    switch (colorMode)
    {
        case ColorMode::RANDOM:
        {
            // return Color(random(MIN_BRIGHTNESS, maxBrightness), random(MIN_BRIGHTNESS, maxBrightness), random(MIN_BRIGHTNESS, maxBrightness));
            return Color(maxBrightness, 0, 0);
        }
        case ColorMode::WHITE_TONES:
        {
            // return Color(random(MIN_BRIGHTNESS, maxBrightness));
            return Color(126, 122, 110);
        }
        default:
        {
            return Color(random(MIN_BRIGHTNESS, maxBrightness), random(MIN_BRIGHTNESS, maxBrightness), random(MIN_BRIGHTNESS, maxBrightness));
        }
    }
}

Color GetNextColor(ColorMode colorMode, Color last)
{
    if (powerMode == PowerMode::OFF) return Color(0);

    switch (colorMode)
    {
        case ColorMode::RANDOM:
        {
            // return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR, last.G() + randomf() * COLOR_CHANGE_FACTOR, last.B() + randomf() * COLOR_CHANGE_FACTOR);

        }
        case ColorMode::WHITE_TONES:
        {
            // return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR);
            return Color(126, 122, 110);
        }
        /// convert it to future color changing based on previous colors
        default:
        {
            return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR, last.G() + randomf() * COLOR_CHANGE_FACTOR, last.B() + randomf() * COLOR_CHANGE_FACTOR);
        }
    }
}
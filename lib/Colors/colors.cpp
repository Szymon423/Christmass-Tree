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
}

Color::Color(float R, float G, float B)
{
    r = ConstrainTo(R, 0.0f,  255.0f);
    g = ConstrainTo(G, 0.0f,  255.0f);
    b = ConstrainTo(B, 0.0f,  255.0f);
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

Color GetColor(ColorMode colorMode)
{
    if (powerMode == PowerMode::OFF) return Color(0);

    int maxBrightness = GetMaxBrightness();
    switch (colorMode)
    {
        case ColorMode::RANDOM:
        {
            return Color(random(MIN_BRIGHTNESS, maxBrightness), random(MIN_BRIGHTNESS, maxBrightness), random(MIN_BRIGHTNESS, maxBrightness));
        }
        case ColorMode::WHITE_TONES:
        {
            return Color(random(MIN_BRIGHTNESS, maxBrightness));
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
            return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR, last.G() + randomf() * COLOR_CHANGE_FACTOR, last.B() + randomf() * COLOR_CHANGE_FACTOR);
        }
        case ColorMode::WHITE_TONES:
        {
            return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR);
        }
        /// convert it to future color changing based on previous colors
        default:
        {
            return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR, last.G() + randomf() * COLOR_CHANGE_FACTOR, last.B() + randomf() * COLOR_CHANGE_FACTOR);
        }
    }
}
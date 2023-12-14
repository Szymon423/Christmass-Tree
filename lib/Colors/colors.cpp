#include "colors.hpp"
#include "modes.hpp"
#include "Arduino.h"
#include "utilities.hpp"
#include "extern.hpp"

Color::Color()
{
    R = 255;
    G = 255;
    B = 255;
}

Color::Color(int rgb)
{
    R = (int)rgb;
    G = (int)rgb;
    B = (int)rgb;
}

Color::Color(int r, int g, int b)
{
    R = (int)r;
    G = (int)g;
    B = (int)b;
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

Color GetNextColor(ColorMode colorMode, Color previousColor, int brightness)
{
    if (powerMode == PowerMode::OFF) return Color(0);

    switch (colorMode)
    {
        case ColorMode::RANDOM:
        {
            return Color(random(MIN_BRIGHTNESS, brightness), random(MIN_BRIGHTNESS, brightness), random(MIN_BRIGHTNESS, brightness));
        }
        case ColorMode::WHITE_TONES:
        {
            return Color(random(MIN_BRIGHTNESS, brightness));
        }
        /// convert it to future color changing based on previous colors
        default:
        {
            return Color(random(MIN_BRIGHTNESS, brightness), random(MIN_BRIGHTNESS, brightness), random(MIN_BRIGHTNESS, brightness));
        }
    }
}
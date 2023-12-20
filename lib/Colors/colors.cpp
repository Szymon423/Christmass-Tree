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
    CartesianToSpherical();
}

Color::Color(float R, float G, float B)
{
    r = ConstrainTo(R, 0.0f,  255.0f);
    g = ConstrainTo(G, 0.0f,  255.0f);
    b = ConstrainTo(B, 0.0f,  255.0f);
    CartesianToSpherical();
}

uint8_t Color::R() const
{
    return r > 255.0f ? 255 : (uint8_t)r;
}

uint8_t Color::G() const
{
    return g > 255.0f ? 255 : (uint8_t)g;
}

uint8_t Color::B() const
{
    return b > 255.0f ? 255 : (uint8_t)b;
}

void Color::Move(float dTheta, float dFi)
{
    CartesianToSpherical();
    theta += dTheta;
    if (theta > TWO_PI) theta -= TWO_PI;
    
    fi += dFi;
    if (fi > TWO_PI) fi -= TWO_PI;
    SphericalToCartesian();
}

void Color::CartesianToSpherical()
{
    float _r = r - COORDINATES_OFFSET;
    float _g = g - COORDINATES_OFFSET;
    float _b = b - COORDINATES_OFFSET;
    radius = sqrtf(powf(_r, 2.0f) + powf(_g, 2.0f) + powf(_b, 2.0f));
    fi = atan2f(sqrtf(powf(_r, 2.0f) + powf(_g, 2.0f)), _b);
    theta = atan2f(_g, _r);
}

void Color::SphericalToCartesian()
{
    r = radius * sinf(fi) * cosf(theta) + COORDINATES_OFFSET;
    g = radius * sinf(fi) * sinf(theta) + COORDINATES_OFFSET;
    b = radius * cosf(fi) + COORDINATES_OFFSET;
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
            Color newColor(0, maxBrightness, 0);
            
            String str("Initial color: [");
            str += String(newColor.r) + ", " + String(newColor.g) + ", " + String(newColor.b) + " - ";
            str += String(newColor.radius) + ", " + String(newColor.theta) + ", " + String(newColor.fi) + "]";
            Serial.println(str);
            return newColor;
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
            last.Move(COLOR_THETA_CHANGE, COLOR_FI_CHANGE);
            String str("Next color: [");
            str += String(last.r) + ", " + String(last.g) + ", " + String(last.b) + " - ";
            str += String(last.radius) + ", " + String(last.theta) + ", " + String(last.fi) + "]";
            Serial.println(str);
            return last;
        }
        case ColorMode::WHITE_TONES:
        {
            // return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR);
            return Color(126, 122, 110);
        }
        /// convert it to future color changing based on previous colors
        default:
        {
            // return Color(last.R() + randomf() * COLOR_CHANGE_FACTOR, last.G() + randomf() * COLOR_CHANGE_FACTOR, last.B() + randomf() * COLOR_CHANGE_FACTOR);
            last.Move(COLOR_THETA_CHANGE, COLOR_FI_CHANGE);
            return last;
        }
    }
}
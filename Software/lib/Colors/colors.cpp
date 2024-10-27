#include "Arduino.h"
#include "log.hpp"
#include "colors.hpp"
#include "modes.hpp"
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

void Color::Move()
{
    static float dTheta{ COLOR_THETA_CHANGE };
    static float dPhi{ COLOR_PHI_CHANGE };
    // CartesianToSpherical();
    radius = GetMaxBrightness();
    if (theta > HALF_PI || theta < 0.0f) dTheta *= (-1.0f); 
    theta += dTheta;
    
    if (phi > HALF_PI || phi < 0.0f) dPhi *= (-1.0f);
    phi += dPhi;

    SphericalToCartesian();
}

void Color::CartesianToSpherical()
{
    radius = sqrtf(powf(r, 2.0f) + powf(g, 2.0f) + powf(b, 2.0f));
    phi = atan2f(sqrtf(powf(r, 2.0f) + powf(g, 2.0f)), b);
    theta = atan2f(g, r);
}

void Color::SphericalToCartesian()
{
    r = ConstrainTo(radius * sinf(phi) * cosf(theta), 0.0f,  255.0f);
    g = ConstrainTo(radius * sinf(phi) * sinf(theta), 0.0f,  255.0f);
    b = ConstrainTo(radius * cosf(phi), 0.0f,  255.0f);
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
            str += String(newColor.radius) + ", " + String(newColor.theta) + ", " + String(newColor.phi) + "]";
            SERIAL_PRINTLN(str);
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
            last.Move();
            String str("Next color: [");
            str += String(last.r) + ", " + String(last.g) + ", " + String(last.b) + " - ";
            str += String(last.radius) + ", " + String(last.theta) + ", " + String(last.phi) + "]";
            SERIAL_PRINTLN(str);
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
            last.Move();
            return last;
        }
    }
}
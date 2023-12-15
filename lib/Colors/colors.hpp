#pragma once
#include "modes.hpp"
#include "stdint.h"



class Color
{
public:
    float r;
    float g;
    float b;

    Color();
    Color(float RGB);
    Color(float R, float G, float B);

    uint8_t R() const;
    uint8_t G() const;
    uint8_t B() const;
};

Color GetColor(ColorMode colorMode);

Color GetNextColor(ColorMode colorMode, Color previousColor);
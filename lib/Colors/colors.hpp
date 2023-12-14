#pragma once
#include "modes.hpp"


class Color
{
public:
    char R;
    char G;
    char B;

    Color();
    Color(int rgb);
    Color(int r, int g, int b);

};

Color GetColor(ColorMode colorMode);

Color GetNextColor(ColorMode colorMode, Color previousColor);
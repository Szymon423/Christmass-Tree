#pragma once
#include "modes.hpp"
#include "stdint.h"



class Color
{
    float r;
    float g;
    float b;
    float fi;
    float theta;
    float radius;

public:
    Color();
    Color(float RGB);
    Color(float R, float G, float B);

    uint8_t R() const;
    uint8_t G() const;
    uint8_t B() const;
};

/// @brief function to convert from cartesian to spherical coordinate system !!!!!!!!!!!!! need to change to use offset
/// @param R value of y
/// @param G value of x
/// @param B value of z
/// @param radius reference value
/// @param theta reference value
/// @param fi reference value
void CartesianToSpherical(float R, float G, float B, float& radius, float& theta, float& fi);

/// @brief function to convert from spherical to cartesian coordinate system !!!!!!!!!!!!! need to change to use offset
/// @param radius 
/// @param theta 
/// @param fi 
/// @param R reference value of y
/// @param G reference value of x
/// @param B reference value of z
void SphericalToCartesian(float radius, float theta, float fi, float& R, float& G, float& B);

Color GetColor(ColorMode colorMode);

Color GetNextColor(ColorMode colorMode, Color previousColor);
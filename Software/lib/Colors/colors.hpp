#pragma once
#include "modes.hpp"
#include "stdint.h"


/// @brief class responsible for nadling color data
class Color
{
public:
    float r;
    float g;
    float b;
    float phi;
    float theta;
    float radius;

    Color();
    Color(float RGB);
    Color(float R, float G, float B);

    /// @brief function to move color point (defined in 3dim cartesian space [R-G-B] and spherical)
    void Move();

    /// @brief function to get R value in uint8_t type
    /// @return R value
    uint8_t R() const;

    /// @brief function to get G value in uint8_t type
    /// @return G value
    uint8_t G() const;

    /// @brief function to get B value in uint8_t type
    /// @return B value
    uint8_t B() const;

    /// @brief function to convert from cartesian to spherical coordinate system
    void CartesianToSpherical();

    /// @brief function to convert from spherical to cartesian coordinate system
    void SphericalToCartesian();
};



/// @brief function to create color based on choosen colorMode
/// @param colorMode is choosen color mode
/// @return Color class object
Color GetColor(ColorMode colorMode);

/// @brief function to create color based on choosen colorMode
/// @param colorMode is choosen color mode
/// @param previousColor previously choosen color
/// @return Color class object
Color GetNextColor(ColorMode colorMode, Color previousColor);
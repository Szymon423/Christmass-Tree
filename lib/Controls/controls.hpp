#pragma once
#include "modes.hpp"
#include <Adafruit_NeoPixel.h>


/// @brief main function to controll LEDs
void LightItUp();

/// @brief function to make smooth blinky-blinky
/// @param previousValue is value previously returned by this function
/// @param speed defines how fast blinks are
/// @param slopeMode determines how the slope is shaped
/// @param done this flag determines if this action finished
/// @return current value of light intensivity
float SmoothBlink(float previousValue, float speed, int brightness, bool& done);

/// @brief function associated with LEDs selection
/// @param colorMode determines colorMode
void PulseIndividualControl(ColorMode colorMode);

/// @brief function associated with LEDs selection
/// @param colorMode determines colorMode
void PulseAllControl(ColorMode colorMode);

/// @brief function associated with LEDs selection (one after another)
/// @param ColorMode determines colorMode
void LinearControl(ColorMode colorMode);

/// @brief turnes off all LEDs
void TurnOffAll();
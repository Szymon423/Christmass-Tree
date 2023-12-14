#pragma once
#include "modes.hpp"
#include <Adafruit_NeoPixel.h>


/// @brief main function to controll LEDs
/// @param colorMode defines color schema
/// @param controlMode defines led order schema
void LightItUp(ColorMode colorMode, ControlMode controlMode);
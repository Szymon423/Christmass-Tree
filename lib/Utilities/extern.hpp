#pragma once

#include "modes.hpp"
#include "definitions.hpp"
#include "Adafruit_NeoPixel.h"

/// @brief globall value defined in main (switch for potentiometer)
extern volatile PotentiometerMode potentiometerMode;

/// @brief globall value defined in main (switch for potentiometer)
extern volatile PowerMode powerMode;

/// @brief globall value defined in main (press time of switch)
extern volatile time change_pin1_time;

/// @brief global value defined in main (delay)
extern int delay_value;

/// @brief global value defined in main (brightness)
extern int max_brightness;

/// @brief global pixels object
extern Adafruit_NeoPixel pixels;
#pragma once

#include "modes.hpp"
#include "definitions.hpp"
#include "Adafruit_NeoPixel.h"


/// @brief globall value defined in main (switch for potentiometer)
extern volatile PowerMode powerMode;

/// @brief globall value defined in main (switch for potentiometer)
extern volatile LightMode lightMode;

/// @brief globall value defined in main (press time of switch)
extern volatile time changeButton1Time;

/// @brief globall value defined in main (press time of switch)
extern volatile time changeButton2Time;

/// @brief global value defined in main (brightness)
extern volatile int maxBrightness;

/// @brief global value telling if mode was changed
extern volatile bool changedLightMode;

/// @brief global value defined in main (delay)
extern int delayValue;

/// @brief global pixels object
extern Adafruit_NeoPixel pixels;
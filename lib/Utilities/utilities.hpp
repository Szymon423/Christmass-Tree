#pragma once

#include "modes.hpp"
#include "definitions.hpp"

/// @brief reads potentiometer
/// @return integer value in range [0, 1024] 
int ReadPotentiometer();

/// @brief function to use in interrupt to controll Potentiometer PotentiometerMode
void ChangePotentiometerMode();

/// @brief function to use in interrupt to controll Power state of LEDs
void ChangePoweMode();

/// @brief function to determine max brightness
/// @return value of max_brightness 
int GetMaxBrightness();

/// @brief function to determine delay
/// @return value of delay in ms 
int GetDelay();

/// @brief function to use in interrupt to register button release time
void RegisterPin1Change();
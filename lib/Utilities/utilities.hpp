#pragma once

#include "modes.hpp"
#include "definitions.hpp"

/// @brief reads potentiometer
/// @return integer value in range [0, 1024] 
int ReadPotentiometer();

/// @brief function to use in interrupt to controll Power state of LEDs
void ChangePoweMode();

/// @brief function to use in interrupt to controll schema of lights
void ChangeLightMode();

/// @brief function to determine max brightness
/// @return value of maxBrightness 
int GetMaxBrightness();

/// @brief function to determine delay
/// @return value of delay in ms 
int GetDelay();

/// @brief function to use in interrupt to register button 1 changes
void RegisterButton1Change();

/// @brief function to use in interrupt to register button 2 changes
void RegisterButton2Change();
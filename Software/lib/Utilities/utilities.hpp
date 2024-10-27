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
/// @return value of maxBrightness (never 0.0f) 
int GetMaxBrightness();

/// @brief function to determine delay
/// @return value of delay in ms 
int GetDelay();

/// @brief function to use in interrupt to register button 1 changes
void RegisterButton1Change();

/// @brief function to use in interrupt to register button 2 changes
void RegisterButton2Change();

/// @brief function to map float value from input range to output range
/// @param X value to be mapped
/// @param minX min possible value of X
/// @param maxX max possible value of X
/// @param minY min possible value of Y
/// @param maxY max possible value of Y
/// @return mapped value of X
float mapf(float X, float minX, float maxX, float minY, float maxY);

/// @brief function to calculate (shortest from two possible) distance between two points assuming first and last led are neighbours
/// @param pointPosition position relative to wchich distance will be calculated
/// @param LEDNumber number of LED to calculate his distance
/// @return calculated distance
float CalculateDistance(float pointPosition, int LEDNumber);

/// @brief function to generate random float based on equation: x = (random(0, 2000) - 1000) / 1000.0f
/// @return value within range [-1.0f - 1.0f]
float randomf();

/// @brief function to clamp x value to range [min max]
/// @param x input value
/// @param min min clamp value
/// @param max max clamp value
/// @return clapmed x value
float ConstrainTo(float x, float min, float max);
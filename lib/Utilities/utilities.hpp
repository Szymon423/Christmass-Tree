#pragma once


/// @brief reads potentiometer
/// @return integer value in range [0, 1024] 
int ReadPotentiometer();


/// @brief defines what is beeing controlled by Potentiometer
enum class Mode
{
    BRIGHTNESS,
    DELAY
};


/// @brief globall value defined in main (switch for potentiometer)
extern volatile Mode mode;


/// @brief function to use in interrupt to controll Potentiometer Mode
void ModeSelector();


/// @brief function to determine max brightness
/// @return value of max_brightness 
int GetBrightness();


/// @brief function to determine delay
/// @return value of delay in ms 
int GetDelay();


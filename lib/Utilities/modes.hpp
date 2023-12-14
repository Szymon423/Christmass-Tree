#pragma once


/// @brief defines what is beeing controlled by Potentiometer
enum class PotentiometerMode
{
    BRIGHTNESS,
    DELAY
};

/// @brief defines how colors are changing
enum class ColorMode
{
    RANDOM,
    WHITE_TONES
};

/// @brief defines how LEDs are glowing (order, direction, etc.)
enum class ControlMode
{
    RANDOM,
    LINEAR,
    BREATHE,
    PULSE
};

/// @brief  defines if LEDs are ON/OFF
enum class PowerMode
{
	ON,
	OFF
};
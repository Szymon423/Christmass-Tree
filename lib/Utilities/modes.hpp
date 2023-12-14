#pragma once


/// @brief defines how LEDs are glowing (order, color)
enum class LightMode
{
    RANDOM_WHITE_TONES,
    RANDOM_RANDOM,
    LINEAR_WHITE_TONES,
    LINEAR_RANDOM,
    PULSE_INDIVIDUAL_WHITE_TONES,
    PULSE_INDIVIDUAL_RANDOM,
    PULSE_ALL_WHITE_TONES,
    PULSE_ALL_RANDOM
};

/// @brief defines how LEDs are glowing (color)
enum class ColorMode
{
    RANDOM,
    WHITE_TONES
};

/// @brief defines how LEDs are glowing (order)
enum class OrderMode
{
    RANDOM,
    LINEAR,
    BREATHE,
    PULSE_INDIVIDUAL,
    PULSE_ALL
};

/// @brief  defines if LEDs are ON/OFF
enum class PowerMode
{
	ON, // LEDs are turned on
	OFF // LEDs are turned off
};

/// @brief defines if edge is rising or falling
enum class Direction 
{
    UP,
    DOWN
};
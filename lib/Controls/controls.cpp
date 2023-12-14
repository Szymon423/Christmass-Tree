#include "controls.hpp"
#include "modes.hpp"
#include "definitions.hpp"
#include "utilities.hpp"
#include "Arduino.h"
#include "colors.hpp"
#include "extern.hpp"


void LightItUp()
{
	if (changedLightMode)
	{
		TurnOffAll();
		changedLightMode = false;
	}

	switch (lightMode)
	{
		case LightMode::RANDOM_WHITE_TONES:
		{
			break;
		}
		case LightMode::RANDOM_RANDOM:
		{
			break;
		}
		case LightMode::LINEAR_WHITE_TONES:
		{
			break;
		}
		case LightMode::LINEAR_RANDOM:
		{
			break;
		}
		case LightMode::PULSE_INDIVIDUAL_WHITE_TONES:
		{
			PulseIndividualControl(ColorMode::WHITE_TONES);
			break;
		}
		case LightMode::PULSE_INDIVIDUAL_RANDOM:
		{
			PulseIndividualControl(ColorMode::RANDOM);
			break;
		}
		case LightMode::PULSE_ALL_WHITE_TONES:
		{
			PulseAllControl(ColorMode::WHITE_TONES);
			break;
		}
		case LightMode::PULSE_ALL_RANDOM:
		{
			PulseAllControl(ColorMode::RANDOM);
			break;
		}
	}
	
}

float SmoothBlink(float previousValue, float speed, int brightness, bool& done)
{
	static Direction direction{ Direction::UP }; 

	float nextValue = previousValue;
	if (previousValue < brightness && direction == Direction::UP) nextValue += speed;
	else 
	{
		nextValue -= speed;
		direction = Direction::DOWN;
	}

	if (nextValue <= 0)
	{
		done = true;
		nextValue = 0;
		direction = Direction::UP;
	}

	return nextValue;
}

void PulseIndividualControl(ColorMode colorMode)
{
	static int currentLED{ 14 };
	static bool done{ false };
	static float previousValue{ 0.0f };
	static Color color = GetColor(colorMode);
	maxBrightness = GetMaxBrightness();
	float change = (float)maxBrightness * DELAY_TIME / BLINK_TIME;
	float brightness = SmoothBlink(previousValue, change, maxBrightness, done);

	Color otherColor = Color(
		(int)((float)color.R * brightness / (float)maxBrightness),
		(int)((float)color.G * brightness / (float)maxBrightness),
		(int)((float)color.B * brightness / (float)maxBrightness)
	);
	
	pixels.setPixelColor(currentLED, pixels.Color(otherColor.R, otherColor.G, otherColor.B)); 
	pixels.show(); 

	if (done) 
	{
		int next;
		do 
		{
		 	next = random(3, LEDS_NUMBER - 1);
		}
		while (next == currentLED);
		currentLED = next;
		done = false;
		color = GetColor(colorMode);
	}

	previousValue = brightness;
}

void PulseAllControl(ColorMode colorMode)
{
	static bool done{ false };
	static float previousValue{ 0.0f };
	static Color color = GetColor(colorMode);
	maxBrightness = GetMaxBrightness();
	float change = (float)maxBrightness * DELAY_TIME / BLINK_TIME;
	float brightness = SmoothBlink(previousValue, change, maxBrightness, done);

	Color otherColor = Color(
		(int)((float)color.R * brightness / (float)maxBrightness),
		(int)((float)color.G * brightness / (float)maxBrightness),
		(int)((float)color.B * brightness / (float)maxBrightness)
	);
	for (int currentLED = 0; currentLED < LEDS_NUMBER; currentLED++)
	{
		pixels.setPixelColor(currentLED, pixels.Color(otherColor.R, otherColor.G, otherColor.B)); 
	}
	pixels.show(); 

	if (done) 
	{
		done = false;
		color = GetColor(colorMode);
	}

	previousValue = brightness;
}

void TurnOffAll()
{
	Color color(0);
	for (int i = 0; i < LEDS_NUMBER; i++)
	{
		pixels.setPixelColor(i, pixels.Color(color.R, color.G, color.B)); 
		pixels.show(); 
	}
}
#include "controls.hpp"
#include "modes.hpp"
#include "definitions.hpp"
#include "utilities.hpp"
#include "Arduino.h"
#include "colors.hpp"
#include "extern.hpp"


void LightItUp(ColorMode colorMode, ControlMode controlMode)
{
    Color color = GetColor(colorMode);
    
    for (int i = 0; i < NUMPIXELS; i++)
	{
		if (potentiometerMode == PotentiometerMode::BRIGHTNESS) max_brightness = GetMaxBrightness();
		else delay_value = GetDelay();
		
        color = GetNextColor(colorMode, color);
		pixels.setPixelColor(i, pixels.Color(color.R, color.G, color.B)); 
		pixels.show(); 
		delay(delay_value); 
	}

	for (int i = 0; i < NUMPIXELS; i++)
	{
		if (potentiometerMode == PotentiometerMode::BRIGHTNESS) max_brightness = GetMaxBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
		pixels.show();
		delay(delay_value);
	}

	for (int i = NUMPIXELS - 1; i > 0; i--)
	{
		if (potentiometerMode == PotentiometerMode::BRIGHTNESS) max_brightness = GetMaxBrightness();
		else delay_value = GetDelay();
		
        color = GetNextColor(colorMode, color);
        pixels.setPixelColor(i, pixels.Color(color.R, color.G, color.B)); 
		pixels.show(); 
		delay(delay_value);
	}

	for (int i = NUMPIXELS - 1; i > 0; i--)
	{
		if (potentiometerMode == PotentiometerMode::BRIGHTNESS) max_brightness = GetMaxBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(0,0,0));
		pixels.show();
		delay(delay_value);
	}
}
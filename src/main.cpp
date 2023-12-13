#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "utilities.hpp"
#include "definitions.hpp"


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
volatile PotentiometerMode mode = PotentiometerMode::BRIGHTNESS;
int delay_value = 50;
int max_brightness = 255;


void setup() 
{
	pixels.begin();
	Serial.begin(9600);
	pinMode(INPUT_1_PIN, INPUT);
  	attachInterrupt(digitalPinToInterrupt(INPUT_1_PIN), ModeSelector, FALLING);
}


void loop() 
{
	for (int i = 0; i < NUMPIXELS; i++)
	{
		if (mode == PotentiometerMode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(random(0, max_brightness), random(0, max_brightness), random(0, max_brightness))); 
		pixels.show(); 
		delay(delay_value); 
	}

	for (int i = 0; i < NUMPIXELS; i++)
	{
		if (mode == PotentiometerMode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
		pixels.show();
		delay(delay_value);
	}

	for (int i = NUMPIXELS - 1; i > 0; i--)
	{
		if (mode == PotentiometerMode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(random(0, max_brightness), random(0, max_brightness), random(0, max_brightness)));
		pixels.show(); 
		delay(delay_value);
	}

	for (int i = NUMPIXELS - 1; i > 0; i--)
	{
		if (mode == PotentiometerMode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(0,0,0));
		pixels.show();
		delay(delay_value);
	}
}
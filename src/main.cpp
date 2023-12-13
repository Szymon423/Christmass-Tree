#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "utilities.hpp"
#include "definitions.hpp"


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int delay_value = 50;
int max_brightness = 255;


volatile Mode mode = Mode::BRIGHTNESS;

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
		if (mode == Mode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(random(0, max_brightness), random(0, max_brightness), random(0, max_brightness))); 
		pixels.show(); 
		delay(delay_value); 
	}

	for (int i = 0; i < NUMPIXELS; i++)
	{
		if (mode == Mode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
		pixels.show();
		delay(delay_value);
	}

	for (int i = NUMPIXELS - 1; i > 0; i--)
	{
		if (mode == Mode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		int max_brightness = map(ReadPotentiometer(), 0, 1023, MIN_BRIGHTNESS, 255);
		pixels.setPixelColor(i, pixels.Color(random(0, max_brightness), random(0, max_brightness), random(0, max_brightness)));
		pixels.show(); 
		delay(delay_value);
	}

	for (int i = NUMPIXELS - 1; i > 0; i--)
	{
		if (mode == Mode::BRIGHTNESS) max_brightness = GetBrightness();
		else delay_value = GetDelay();
		
		pixels.setPixelColor(i, pixels.Color(0,0,0));
		pixels.show();
		delay(delay_value);
	}
}
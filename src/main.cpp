#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


#define PIN            7
#define NUMPIXELS      26 

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() 
{
	// For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
	for(int i=0;i<NUMPIXELS;i++)
	{
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		pixels.setPixelColor(i, pixels.Color(random(0, 50), random(0, 50), random(0, 50))); // Moderately bright green color.

		pixels.show(); // This sends the updated pixel color to the hardware.

		delay(delayval); // Delay for a period of time (in milliseconds).
	}

	for(int i=0;i<NUMPIXELS;i++)
	{
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.

		pixels.show(); // This sends the updated pixel color to the hardware.

		delay(delayval); // Delay for a period of time (in milliseconds).
	}

	for(int i=NUMPIXELS - 1;i>0;i--)
	{
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		pixels.setPixelColor(i, pixels.Color(random(0, 50), random(0, 50), random(0, 50))); // Moderately bright green color.

		pixels.show(); // This sends the updated pixel color to the hardware.

		delay(delayval); // Delay for a period of time (in milliseconds).
	}

	for(int i=NUMPIXELS - 1;i>0;i--)
	{
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

		pixels.show(); // This sends the updated pixel color to the hardware.

		delay(delayval); // Delay for a period of time (in milliseconds).
	}
}
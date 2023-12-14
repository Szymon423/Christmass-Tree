#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "utilities.hpp"
#include "definitions.hpp"
#include "controls.hpp"
#include "modes.hpp"


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
volatile PotentiometerMode potentiometerMode = PotentiometerMode::BRIGHTNESS;
volatile PowerMode powerMode = PowerMode::ON;
int delay_value = 50;
int max_brightness = 255;
volatile time change_pin1_time = 0;


void setup() 
{
	pixels.begin();
	Serial.begin(9600);
	pinMode(INPUT_1_PIN, INPUT);
  	attachInterrupt(digitalPinToInterrupt(INPUT_1_PIN), RegisterPin1Change, CHANGE);
}


void loop() 
{
	LightItUp(ColorMode::WHITE_TONES, ControlMode::LINEAR);
}
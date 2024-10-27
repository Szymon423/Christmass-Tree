#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "utilities.hpp"
#include "definitions.hpp"
#include "controls.hpp"
#include "modes.hpp"
#include "log.hpp"


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDS_NUMBER, LED_PIN, NEO_GRB + NEO_KHZ800);
volatile PowerMode powerMode = PowerMode::ON;
volatile LightMode lightMode = LightMode::LINEAR_RANDOM;
volatile time changeButton1Time = 0;
volatile time changeButton2Time = 0;
volatile int maxBrightness = 255;
volatile bool changedLightMode = false;
int delayValue = 50;


void setup() 
{
	pixels.begin();
	SERIAL_BEGIN(9600);
	delay(2000);
	pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  	attachInterrupt(digitalPinToInterrupt(BUTTON_1_PIN), RegisterButton1Change, CHANGE);
  	attachInterrupt(digitalPinToInterrupt(BUTTON_2_PIN), RegisterButton2Change, CHANGE);
	TurnOffAll();
	maxBrightness = GetMaxBrightness();
	pixels.setBrightness(100);
}


void loop() 
{
	LightItUp();
	delay(DELAY_TIME);
}
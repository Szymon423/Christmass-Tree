#include "utilities.hpp"
#include "Arduino.h"
#include "definitions.hpp"
#include "extern.hpp"



int ReadPotentiometer()
{
    return analogRead(POTENTIOMETER_PIN);
}

void ChangePotentiometerMode()
{
    if (potentiometerMode == PotentiometerMode::BRIGHTNESS) 
    {
        potentiometerMode = PotentiometerMode::DELAY;
        return;
    }
    potentiometerMode = PotentiometerMode::BRIGHTNESS;
}

void ChangePoweMode()
{
    if (powerMode == PowerMode::ON) 
    {
        powerMode = PowerMode::OFF;
        return;
    }
    powerMode = PowerMode::ON;
}

int GetDelay()
{
    return map(ReadPotentiometer(), 0, 1023, MIN_DELAY, MAX_DELAY);
}

int GetMaxBrightness()
{
    return map(ReadPotentiometer(), 0, 1023, MAX_BRIGHTNESS, MIN_BRIGHTNESS);
}

void RegisterPin1Change()
{
    if (digitalRead(INPUT_1_PIN) == LOW)
    {
        change_pin1_time = millis();
        return; 
    }

    if (millis() - change_pin1_time <= DEBOUNCE_TIME_MS) 
    {
        return;    
    }

    if (millis() - change_pin1_time > LONG_PRESS_TIME_MS)
    {
        ChangePoweMode();
        return;
    }

    ChangePotentiometerMode();
}
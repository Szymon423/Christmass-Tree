#include "utilities.hpp"
#include "Arduino.h"
#include "definitions.hpp"
#include "extern.hpp"



int ReadPotentiometer()
{
    return analogRead(POTENTIOMETER_PIN);
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

void ChangeLightMode()
{
    switch (lightMode)
    {
        case LightMode::PULSE_INDIVIDUAL_WHITE_TONES: 
        {
            lightMode = LightMode::PULSE_INDIVIDUAL_RANDOM;
            break;
        }
        case LightMode::PULSE_INDIVIDUAL_RANDOM: 
        {
            lightMode = LightMode::PULSE_ALL_WHITE_TONES;
            break;
        }
        case LightMode::PULSE_ALL_WHITE_TONES: 
        {
            lightMode = LightMode::PULSE_ALL_RANDOM;
            break;
        }
        case LightMode::PULSE_ALL_RANDOM: 
        {
            lightMode = LightMode::PULSE_INDIVIDUAL_WHITE_TONES;
            break;
        }
    }
    changedLightMode = true;
}

int GetDelay()
{
    return 200;
}

int GetMaxBrightness()
{
    return map(ReadPotentiometer(), 0, 1023, MAX_BRIGHTNESS, MIN_BRIGHTNESS);
}

void RegisterButton1Change()
{
    if (digitalRead(BUTTON_1_PIN) == LOW)
    {
        changeButton1Time = millis();
        return; 
    }
    if (millis() - changeButton1Time < LONG_PRESS_TIME_MS) return;
    ChangePoweMode();
}

void RegisterButton2Change()
{
    if (digitalRead(BUTTON_2_PIN) == LOW)
    {
        changeButton1Time = millis();
        return; 
    }
    if (millis() - changeButton1Time < DEBOUNCE_TIME_MS) return;
    ChangeLightMode();
}
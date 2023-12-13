#include "utilities.hpp"
#include "Arduino.h"
#include "definitions.hpp"



int ReadPotentiometer()
{
    return analogRead(POTENTIOMETER_PIN);
}

void ModeSelector()
{
    if (mode == PotentiometerMode::BRIGHTNESS) 
    {
        mode = PotentiometerMode::DELAY;
        return;
    }
    mode = PotentiometerMode::BRIGHTNESS;
}

int GetDelay()
{
    return map(ReadPotentiometer(), 0, 1023, MIN_DELAY, MAX_DELAY);
}

int GetBrightness()
{
    return map(ReadPotentiometer(), 0, 1023, 255, MIN_BRIGHTNESS);
}
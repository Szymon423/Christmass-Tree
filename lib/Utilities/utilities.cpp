#include "utilities.hpp"
#include "Arduino.h"
#include "definitions.hpp"



int ReadPotentiometer()
{
    return analogRead(POTENTIOMETER_PIN);
}

void ModeSelector()
{
    if (mode == Mode::BRIGHTNESS) 
    {
        mode = Mode::DELAY;
        return;
    }
    mode = Mode::BRIGHTNESS;
}

int GetDelay()
{
    return map(ReadPotentiometer(), 0, 1023, MIN_DELAY, MAX_DELAY);
}

int GetBrightness()
{
    return map(ReadPotentiometer(), 0, 1023, MIN_BRIGHTNESS, 255);
}
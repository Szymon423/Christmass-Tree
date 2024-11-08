#pragma once
#include "Arduino.h"


namespace Constants {
    constexpr uint8_t PixelsPin = 7;
    constexpr uint8_t PixelsNumber = 25;
    constexpr uint8_t EncoderButtonPin = 0;
    constexpr uint8_t EncoderAPin = 1;
    constexpr uint8_t EncoderBPin = 2;
    constexpr uint8_t MaxBrightness = 200;
    constexpr uint8_t MinBrightness = 10;
    constexpr uint8_t DelayTimeMs = 10;
    constexpr uint16_t BlinkTimeMs = 500;
    constexpr uint8_t WindowSize = 2.0f;
    constexpr uint8_t ColocChangeCycle = 200;
    constexpr float ColorChangeFactor = 1.0f;
    constexpr float LinearMoveIncrement = 0.005f;
    constexpr float ColorThetaChange = 0.03f;
    constexpr float ColorPhiChange =  0.07f;
    constexpr float CoordinatesOffset = 127.0f;
}

#define CONSOLE_LOG
using time = unsigned long;
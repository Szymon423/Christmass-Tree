#include "definitions.hpp"
#include <Arduino.h>

#ifdef CONSOLE_LOG
    #define SERIAL_BEGIN(...)   Serial.begin(__VA_ARGS__)
    #define SERIAL_PRINTLN(...) Serial.println(__VA_ARGS__)
    #define SERIAL_PRINT(...)   Serial.print(__VA_ARGS__)
#else
    #define SERIAL_BEGIN(...)   (void)0
    #define SERIAL_PRINTLN(...) (void)0
    #define SERIAL_PRINT(...)   (void)0
#endif
#include <Adafruit_NeoPixel.h>
#include <Encoder.h>
#include "definitions.hpp"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(Constants::PixelsNumber, Constants::PixelsPin, NEO_GRB + NEO_KHZ800);
Encoder encoder(Constants::EncoderBPin, Constants::EncoderAPin);

volatile int mode = 0;
int brightness = 80;
long oldPosition = 0;
long firstPixelHue = 0;
float currentPixel = 0.0; // Zmieniono na float
int breathIndex = 0;

void changeMode();
void rainbowCycleStep();
void colorWipeStep(bool colorful);
void randomFlashesStep(bool colorful);
void breathingStep(bool colorful);
void solidColorStep(); // Nowa funkcja

void setup() {
    pinMode(Constants::EncoderButtonPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(Constants::EncoderButtonPin), changeMode, FALLING);
    pixels.begin();
    pixels.show();
}

void loop() {
    long newPosition = encoder.read();
    if (newPosition != oldPosition) {
        oldPosition = newPosition;
        brightness = constrain(map(newPosition, 0, 192, 0, 255), 0, 255); // Zmieniono max pozycje enkodera na 96
    }

    switch (mode) {
        case 0:
            rainbowCycleStep();
            break;
        case 1:
            breathingStep(false);
            break;
        case 2:
            breathingStep(true);
            break;
        case 3:
            colorWipeStep(false);
            break;
        case 4:
            colorWipeStep(true);
            break;
        case 5:
            randomFlashesStep(false);
            break;
        case 6:
            randomFlashesStep(true);
            break;
        case 7:
            solidColorStep(); // Nowy tryb
            break;
        default:
            mode = 0;
            break;
    }
    delay(20);
}

void changeMode() {
    mode = (mode + 1) % 8; // Zmieniono na 8, aby uwzględnić nowy tryb
}

void rainbowCycleStep() {
    for (int i = 0; i < pixels.numPixels(); i++) {
        int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
        pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.setBrightness(brightness);
    pixels.show();
    firstPixelHue += 256;
    if (firstPixelHue >= 5 * 65536) {
        firstPixelHue = 0;
    }
}

void breathingStep(bool colorful) {
    breathIndex = (breathIndex + 1) % 1024;
    int breathBrightness = (exp(sin(breathIndex / 1024.0 * PI)) - 0.36787944) * 108.0;
    breathBrightness = map(breathBrightness, 0, 108, 0, brightness);

    if (colorful) {
        for (int i = 0; i < pixels.numPixels(); i++) {
            int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
            uint32_t color = pixels.gamma32(pixels.ColorHSV(pixelHue));
            pixels.setPixelColor(i, pixels.Color(
                (color >> 16 & 0xFF) * breathBrightness / 255,
                (color >> 8 & 0xFF) * breathBrightness / 255,
                (color & 0xFF) * breathBrightness / 255
            ));
        }
    } else {
        pixels.fill(pixels.Color(255, 223, 186));
        pixels.setBrightness(breathBrightness);
    }
    pixels.show();

    if (colorful) {
        firstPixelHue += 64;
    }
}

void randomFlashesStep(bool colorful) {
    static int flashBrightness[Constants::PixelsNumber] = {0};
    static int flashDecay[Constants::PixelsNumber] = {0};

    int numFlashes = random(1, 6);
    for (int n = 0; n < numFlashes; n++) {
        int pixel = random(Constants::PixelsNumber);
        if (flashBrightness[pixel] == 0) {
            flashBrightness[pixel] = random(128, 256);
            flashDecay[pixel] = random(1, 5);
        }
    }

    for (int i = 0; i < Constants::PixelsNumber; i++) {
        if (flashBrightness[i] > 0) {
            if (colorful) {
                int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
                uint32_t color = pixels.gamma32(pixels.ColorHSV(pixelHue));
                pixels.setPixelColor(i, pixels.Color(
                    (color >> 16 & 0xFF) * flashBrightness[i] / 255,
                    (color >> 8 & 0xFF) * flashBrightness[i] / 255,
                    (color & 0xFF) * flashBrightness[i] / 255
                ));
            } else {
                pixels.setPixelColor(i, pixels.Color(flashBrightness[i], flashBrightness[i], flashBrightness[i]));
            }
            flashBrightness[i] -= flashDecay[i];
            if (flashBrightness[i] < 0) flashBrightness[i] = 0;
        } else {
            pixels.setPixelColor(i, 0);
        }
    }
    pixels.setBrightness(brightness);
    pixels.show();

    if (colorful) {
        firstPixelHue += 64;
    }
}

void colorWipeStep(bool colorful) {
    const float fadeDistance = 3.0;
    pixels.clear();

    for (int i = 0; i < pixels.numPixels(); i++) {
        float distance = fabs(currentPixel - i);
        if (distance < fadeDistance) {
            float intensity = 1.0 - (distance / fadeDistance);
            int pixelBrightness = intensity * brightness;
            if (colorful) {
                int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
                uint32_t color = pixels.gamma32(pixels.ColorHSV(pixelHue));
                pixels.setPixelColor(i, pixels.Color(
                    (color >> 16 & 0xFF) * pixelBrightness / 255,
                    (color >> 8 & 0xFF) * pixelBrightness / 255,
                    (color & 0xFF) * pixelBrightness / 255
                ));
            } else {
                pixels.setPixelColor(i, pixels.Color(
                    255 * pixelBrightness / 255,
                    223 * pixelBrightness / 255,
                    186 * pixelBrightness / 255
                ));
            }
        }
    }
    pixels.setBrightness(brightness);
    pixels.show();
    currentPixel += 0.1;
    if (currentPixel >= pixels.numPixels()) {
        currentPixel -= pixels.numPixels();
    }

    if (colorful) {
        firstPixelHue += 64;
    }
}

void solidColorStep() {
    int pixelHue = firstPixelHue;
    uint32_t color = pixels.gamma32(pixels.ColorHSV(pixelHue));
    pixels.fill(color);
    pixels.setBrightness(brightness);
    pixels.show();
    firstPixelHue += 64; // Wolniejsza zmiana koloru
    if (firstPixelHue >= 65536) {
        firstPixelHue = 0;
    }
}

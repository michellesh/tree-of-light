#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>
#include "secrets.h"
#include "globals.h"
#include <WiFi.h>

long start;

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  initArrays();
  initLEDs();
}

void loop() {
  start = micros();

  juggle();
  FastLED.show();

  // Print the loop cycle time
  EVERY_N_SECONDS(1) {
    Serial.println(micros() - start);
  }
}

void juggle() {
  int numLeds;
  for(uint16_t discIndex = 0; discIndex < NUM_DISCS; discIndex++) {
    numLeds = getNumLeds(discIndex);
    for(uint16_t stripIndex = 0; stripIndex < NUM_STRIPS_PER_DISC; stripIndex++) {
      CRGB *strip = getStrip(discIndex, stripIndex);
      fadeToBlackBy(strip, numLeds, 20);
    }
  }

  uint8_t dothue = 0;
  for(uint16_t discIndex = 0; discIndex < NUM_DISCS; discIndex++) {
    numLeds = getNumLeds(discIndex);
    for(uint16_t stripIndex = 0; stripIndex < NUM_STRIPS_PER_DISC; stripIndex++) {
      CRGB *strip = getStrip(discIndex, stripIndex);

      for (int j = 0; j < 8; j++) {
        int pixelIndex = beatsin16(j + 7, 0, numLeds - 1);
        CRGB color = strip[pixelIndex];
        color |= CHSV(dothue, 200, 255);
        setLED(discIndex, stripIndex, pixelIndex, color);
        dothue += 32;
      }
    }
  }
}

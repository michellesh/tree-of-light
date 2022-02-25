#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <Arduino.h>
#include <FastLED.h>
#include "secrets.h"
#include "globals.h"
#include <WiFi.h>

#define DATA_PIN_00   2
#define DATA_PIN_01   4
#define DATA_PIN_02   5
#define DATA_PIN_03   12
#define DATA_PIN_04   13
#define DATA_PIN_05   14
#define DATA_PIN_06   18
#define DATA_PIN_07   19
#define DATA_PIN_08   21
#define DATA_PIN_09   22
#define DATA_PIN_10   23
#define DATA_PIN_11   25
#define DATA_PIN_12   26
#define DATA_PIN_13   27
#define DATA_PIN_14   32
#define DATA_PIN_15   33

#define BRIGHTNESS   255
#define COLOR_ORDER  GRB
#define LED_TYPE     WS2813

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  uint8_t discIndex = getDiscIndex();
  initArrays();
  initLEDs(discIndex);
}

void loop() {
  for(uint16_t disc = 0; disc < NUM_DISCS; disc++) {
    for(uint16_t strip = 0; strip < NUM_STRIPS_PER_DISC; strip++) {
      for(uint16_t pixel = 0; pixel < getNumLeds(disc); pixel++) {
        setLED(disc, strip, pixel, CRGB::Blue);
      }
    }
  }
  FastLED.show();
  delay(2000);
  for(uint16_t disc = 0; disc < NUM_DISCS; disc++) {
    for(uint16_t strip = 0; strip < NUM_STRIPS_PER_DISC; strip++) {
      for(uint16_t pixel = 0; pixel < getNumLeds(disc); pixel++) {
        setLED(disc, strip, pixel, CRGB::Black);
      }
    }
  }
  FastLED.show();
  delay(2000);
}

#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

#define DATA_PIN    23
#define LED_TYPE    WS2813
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define BRIGHTNESS  255

CRGB *leds;

long start;

void setup() {
  Serial.begin(115200);
  delay(500);
  leds = new CRGB[NUM_LEDS];
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
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
  fadeToBlackBy(leds, NUM_LEDS, 20);

  uint8_t dothue = 0;
  for (int j = 0; j < 8; j++) {
    leds[beatsin16(j + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

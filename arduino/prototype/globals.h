#define NUM_DISCS  9

#define PIN_1  2
#define PIN_2  4
#define PIN_3  5
#define PIN_4  12
#define PIN_5  13
#define PIN_6  14
#define PIN_7  18

#define NUM_LEDS_PIN_1  200
#define NUM_LEDS_PIN_2  184
#define NUM_LEDS_PIN_3  196
#define NUM_LEDS_PIN_4  202
#define NUM_LEDS_PIN_5  198
#define NUM_LEDS_PIN_6  190
#define NUM_LEDS_PIN_7  114

CRGB LEDS_PIN_1[NUM_LEDS_PIN_1];
CRGB LEDS_PIN_2[NUM_LEDS_PIN_2];
CRGB LEDS_PIN_3[NUM_LEDS_PIN_3];
CRGB LEDS_PIN_4[NUM_LEDS_PIN_4];
CRGB LEDS_PIN_5[NUM_LEDS_PIN_5];
CRGB LEDS_PIN_6[NUM_LEDS_PIN_6];
CRGB LEDS_PIN_7[NUM_LEDS_PIN_7];

int16_t NUM_LEDS_TOTAL = NUM_LEDS_PIN_1 +
                         NUM_LEDS_PIN_2 +
                         NUM_LEDS_PIN_3 +
                         NUM_LEDS_PIN_4 +
                         NUM_LEDS_PIN_5 +
                         NUM_LEDS_PIN_6 +
                         NUM_LEDS_PIN_7;

uint8_t NUM_LEDS_DISC[] = {240, 216, 186, 168, 150, 120, 90, 72, 42};

uint8_t getDiscIndex() {
  return WiFi.macAddress() == tol_macAddressStr0 ? 0
         : WiFi.macAddress() == tol_macAddressStr1 ? 1
         : WiFi.macAddress() == tol_macAddressStr2 ? 2
         : WiFi.macAddress() == tol_macAddressStr3 ? 3
         : WiFi.macAddress() == tol_macAddressStr4 ? 4
         : WiFi.macAddress() == tol_macAddressStr5 ? 5
         : WiFi.macAddress() == tol_macAddressStr6 ? 6
         : WiFi.macAddress() == tol_macAddressStr7 ? 7
                                                   : 8;
}

void initArrays() {
  DISC_0_STRIP_00 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_01 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_02 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_03 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_04 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_05 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_06 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_07 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_08 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_09 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_10 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_11 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_12 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_13 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_14 = new CRGB[NUM_LEDS_DISC_0];
  DISC_0_STRIP_15 = new CRGB[NUM_LEDS_DISC_0];

  DISC_1_STRIP_00 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_01 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_02 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_03 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_04 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_05 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_06 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_07 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_08 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_09 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_10 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_11 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_12 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_13 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_14 = new CRGB[NUM_LEDS_DISC_1];
  DISC_1_STRIP_15 = new CRGB[NUM_LEDS_DISC_1];

  DISC_2_STRIP_00 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_01 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_02 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_03 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_04 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_05 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_06 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_07 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_08 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_09 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_10 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_11 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_12 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_13 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_14 = new CRGB[NUM_LEDS_DISC_2];
  DISC_2_STRIP_15 = new CRGB[NUM_LEDS_DISC_2];

  DISC_3_STRIP_00 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_01 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_02 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_03 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_04 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_05 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_06 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_07 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_08 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_09 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_10 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_11 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_12 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_13 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_14 = new CRGB[NUM_LEDS_DISC_3];
  DISC_3_STRIP_15 = new CRGB[NUM_LEDS_DISC_3];

  DISC_4_STRIP_00 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_01 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_02 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_03 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_04 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_05 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_06 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_07 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_08 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_09 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_10 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_11 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_12 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_13 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_14 = new CRGB[NUM_LEDS_DISC_4];
  DISC_4_STRIP_15 = new CRGB[NUM_LEDS_DISC_4];

  DISC_5_STRIP_00 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_01 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_02 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_03 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_04 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_05 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_06 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_07 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_08 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_09 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_10 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_11 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_12 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_13 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_14 = new CRGB[NUM_LEDS_DISC_5];
  DISC_5_STRIP_15 = new CRGB[NUM_LEDS_DISC_5];

  DISC_6_STRIP_00 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_01 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_02 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_03 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_04 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_05 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_06 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_07 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_08 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_09 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_10 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_11 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_12 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_13 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_14 = new CRGB[NUM_LEDS_DISC_6];
  DISC_6_STRIP_15 = new CRGB[NUM_LEDS_DISC_6];

  DISC_7_STRIP_00 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_01 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_02 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_03 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_04 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_05 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_06 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_07 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_08 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_09 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_10 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_11 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_12 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_13 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_14 = new CRGB[NUM_LEDS_DISC_7];
  DISC_7_STRIP_15 = new CRGB[NUM_LEDS_DISC_7];

  DISC_8_STRIP_00 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_01 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_02 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_03 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_04 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_05 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_06 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_07 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_08 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_09 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_10 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_11 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_12 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_13 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_14 = new CRGB[NUM_LEDS_DISC_8];
  DISC_8_STRIP_15 = new CRGB[NUM_LEDS_DISC_8];
}

void initLEDs() {
  uint8_t discIndex = getDiscIndex();
  int numLeds = getNumLeds(discIndex);
  switch (discIndex) {
    case 0:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_0_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_0_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_0_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_0_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_0_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_0_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_0_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_0_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_0_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_0_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_0_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_0_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_0_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_0_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_0_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_0_STRIP_15, numLeds);
      break;
    case 1:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_1_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_1_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_1_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_1_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_1_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_1_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_1_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_1_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_1_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_1_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_1_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_1_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_1_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_1_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_1_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_1_STRIP_15, numLeds);
      break;
    case 2:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_2_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_2_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_2_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_2_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_2_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_2_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_2_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_2_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_2_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_2_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_2_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_2_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_2_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_2_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_2_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_2_STRIP_15, numLeds);
      break;
    case 3:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_3_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_3_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_3_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_3_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_3_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_3_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_3_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_3_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_3_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_3_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_3_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_3_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_3_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_3_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_3_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_3_STRIP_15, numLeds);
      break;
    case 4:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_4_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_4_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_4_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_4_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_4_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_4_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_4_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_4_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_4_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_4_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_4_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_4_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_4_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_4_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_4_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_4_STRIP_15, numLeds);
      break;
    case 5:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_5_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_5_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_5_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_5_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_5_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_5_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_5_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_5_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_5_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_5_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_5_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_5_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_5_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_5_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_5_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_5_STRIP_15, numLeds);
      break;
    case 6:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_6_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_6_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_6_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_6_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_6_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_6_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_6_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_6_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_6_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_6_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_6_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_6_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_6_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_6_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_6_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_6_STRIP_15, numLeds);
      break;
    case 7:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_7_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_7_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_7_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_7_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_7_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_7_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_7_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_7_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_7_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_7_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_7_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_7_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_7_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_7_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_7_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_7_STRIP_15, numLeds);
      break;
    case 8:
      FastLED.addLeds<LED_TYPE, DATA_PIN_00, COLOR_ORDER>(DISC_8_STRIP_00, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_01, COLOR_ORDER>(DISC_8_STRIP_01, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_02, COLOR_ORDER>(DISC_8_STRIP_02, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_03, COLOR_ORDER>(DISC_8_STRIP_03, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_04, COLOR_ORDER>(DISC_8_STRIP_04, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_05, COLOR_ORDER>(DISC_8_STRIP_05, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_06, COLOR_ORDER>(DISC_8_STRIP_06, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_07, COLOR_ORDER>(DISC_8_STRIP_07, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_08, COLOR_ORDER>(DISC_8_STRIP_08, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_09, COLOR_ORDER>(DISC_8_STRIP_09, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_10, COLOR_ORDER>(DISC_8_STRIP_10, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_11, COLOR_ORDER>(DISC_8_STRIP_11, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_12, COLOR_ORDER>(DISC_8_STRIP_12, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_13, COLOR_ORDER>(DISC_8_STRIP_13, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_14, COLOR_ORDER>(DISC_8_STRIP_14, numLeds);
      FastLED.addLeds<LED_TYPE, DATA_PIN_15, COLOR_ORDER>(DISC_8_STRIP_15, numLeds);
      break;
  }

  FastLED.setBrightness(BRIGHTNESS);
}

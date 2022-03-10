int getNumLeds(int discIndex) {
  return discIndex == 0 ? NUM_LEDS_DISC_0
         : discIndex == 1 ? NUM_LEDS_DISC_1
         : discIndex == 2 ? NUM_LEDS_DISC_2
         : discIndex == 3 ? NUM_LEDS_DISC_3
         : discIndex == 4 ? NUM_LEDS_DISC_4
         : discIndex == 5 ? NUM_LEDS_DISC_5
         : discIndex == 6 ? NUM_LEDS_DISC_6
         : discIndex == 7 ? NUM_LEDS_DISC_7
                          : NUM_LEDS_DISC_8;
}

void setLED(int discIndex, int stripIndex, int pixelIndex, CRGB color) {
  if (discIndex == 0) {
    switch (stripIndex) {
      case 0: DISC_0_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_0_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_0_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_0_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_0_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_0_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_0_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_0_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_0_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_0_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_0_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_0_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_0_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_0_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_0_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_0_STRIP_15[pixelIndex] = color; break;
    }
  } else if (discIndex == 1) {
    switch (stripIndex) {
      case 0: DISC_1_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_1_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_1_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_1_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_1_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_1_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_1_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_1_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_1_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_1_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_1_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_1_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_1_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_1_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_1_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_1_STRIP_15[pixelIndex] = color; break;
    }
  } else if (discIndex == 2) {
    switch (stripIndex) {
      case 0: DISC_2_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_2_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_2_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_2_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_2_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_2_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_2_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_2_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_2_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_2_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_2_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_2_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_2_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_2_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_2_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_2_STRIP_15[pixelIndex] = color; break;
    }
  } else if (discIndex == 3) {
    switch (stripIndex) {
      case 0: DISC_3_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_3_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_3_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_3_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_3_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_3_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_3_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_3_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_3_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_3_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_3_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_3_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_3_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_3_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_3_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_3_STRIP_15[pixelIndex] = color; break;
    }
  } else if (discIndex == 4) {
    switch (stripIndex) {
      case 0: DISC_4_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_4_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_4_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_4_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_4_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_4_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_4_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_4_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_4_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_4_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_4_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_4_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_4_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_4_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_4_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_4_STRIP_15[pixelIndex] = color; break;
    }
  } else if (discIndex == 5) {
    switch (stripIndex) {
      case 0: DISC_5_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_5_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_5_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_5_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_5_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_5_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_5_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_5_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_5_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_5_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_5_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_5_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_5_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_5_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_5_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_5_STRIP_15[pixelIndex] = color; break;
    }
  } else if (discIndex == 6) {
    switch (stripIndex) {
      case 0: DISC_6_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_6_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_6_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_6_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_6_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_6_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_6_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_6_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_6_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_6_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_6_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_6_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_6_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_6_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_6_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_6_STRIP_15[pixelIndex] = color; break;
    }
  } else if (discIndex == 7) {
    switch (stripIndex) {
      case 0: DISC_7_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_7_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_7_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_7_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_7_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_7_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_7_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_7_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_7_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_7_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_7_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_7_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_7_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_7_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_7_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_7_STRIP_15[pixelIndex] = color; break;
    }
  } else {
    switch (stripIndex) {
      case 0: DISC_8_STRIP_00[pixelIndex] = color; break;
      case 1: DISC_8_STRIP_01[pixelIndex] = color; break;
      case 2: DISC_8_STRIP_02[pixelIndex] = color; break;
      case 3: DISC_8_STRIP_03[pixelIndex] = color; break;
      case 4: DISC_8_STRIP_04[pixelIndex] = color; break;
      case 5: DISC_8_STRIP_05[pixelIndex] = color; break;
      case 6: DISC_8_STRIP_06[pixelIndex] = color; break;
      case 7: DISC_8_STRIP_07[pixelIndex] = color; break;
      case 8: DISC_8_STRIP_08[pixelIndex] = color; break;
      case 9: DISC_8_STRIP_09[pixelIndex] = color; break;
      case 10: DISC_8_STRIP_10[pixelIndex] = color; break;
      case 11: DISC_8_STRIP_11[pixelIndex] = color; break;
      case 12: DISC_8_STRIP_12[pixelIndex] = color; break;
      case 13: DISC_8_STRIP_13[pixelIndex] = color; break;
      case 14: DISC_8_STRIP_14[pixelIndex] = color; break;
      case 15: DISC_8_STRIP_15[pixelIndex] = color; break;
    }
  }
}

CRGB getLED(int discIndex, int stripIndex, int pixelIndex) {
  CRGB *strip = getStrip(discIndex, stripIndex);
  return strip[pixelIndex];
}

CRGB* getStrip(int discIndex, int stripIndex) {
  if (discIndex == 0) {
    switch (stripIndex) {
      case  0: return DISC_0_STRIP_00;
      case  1: return DISC_0_STRIP_01;
      case  2: return DISC_0_STRIP_02;
      case  3: return DISC_0_STRIP_03;
      case  4: return DISC_0_STRIP_04;
      case  5: return DISC_0_STRIP_05;
      case  6: return DISC_0_STRIP_06;
      case  7: return DISC_0_STRIP_07;
      case  8: return DISC_0_STRIP_08;
      case  9: return DISC_0_STRIP_09;
      case 10: return DISC_0_STRIP_10;
      case 11: return DISC_0_STRIP_11;
      case 12: return DISC_0_STRIP_12;
      case 13: return DISC_0_STRIP_13;
      case 14: return DISC_0_STRIP_14;
      case 15: return DISC_0_STRIP_15;
    }
  } else if (discIndex == 1) {
    switch (stripIndex) {
      case  0: return DISC_1_STRIP_00;
      case  1: return DISC_1_STRIP_01;
      case  2: return DISC_1_STRIP_02;
      case  3: return DISC_1_STRIP_03;
      case  4: return DISC_1_STRIP_04;
      case  5: return DISC_1_STRIP_05;
      case  6: return DISC_1_STRIP_06;
      case  7: return DISC_1_STRIP_07;
      case  8: return DISC_1_STRIP_08;
      case  9: return DISC_1_STRIP_09;
      case 10: return DISC_1_STRIP_10;
      case 11: return DISC_1_STRIP_11;
      case 12: return DISC_1_STRIP_12;
      case 13: return DISC_1_STRIP_13;
      case 14: return DISC_1_STRIP_14;
      case 15: return DISC_1_STRIP_15;
    }
  } else if (discIndex == 2) {
    switch (stripIndex) {
      case  0: return DISC_2_STRIP_00;
      case  1: return DISC_2_STRIP_01;
      case  2: return DISC_2_STRIP_02;
      case  3: return DISC_2_STRIP_03;
      case  4: return DISC_2_STRIP_04;
      case  5: return DISC_2_STRIP_05;
      case  6: return DISC_2_STRIP_06;
      case  7: return DISC_2_STRIP_07;
      case  8: return DISC_2_STRIP_08;
      case  9: return DISC_2_STRIP_09;
      case 10: return DISC_2_STRIP_10;
      case 11: return DISC_2_STRIP_11;
      case 12: return DISC_2_STRIP_12;
      case 13: return DISC_2_STRIP_13;
      case 14: return DISC_2_STRIP_14;
      case 15: return DISC_2_STRIP_15;
    }
  } else if (discIndex == 3) {
    switch (stripIndex) {
      case  0: return DISC_3_STRIP_00;
      case  1: return DISC_3_STRIP_01;
      case  2: return DISC_3_STRIP_02;
      case  3: return DISC_3_STRIP_03;
      case  4: return DISC_3_STRIP_04;
      case  5: return DISC_3_STRIP_05;
      case  6: return DISC_3_STRIP_06;
      case  7: return DISC_3_STRIP_07;
      case  8: return DISC_3_STRIP_08;
      case  9: return DISC_3_STRIP_09;
      case 10: return DISC_3_STRIP_10;
      case 11: return DISC_3_STRIP_11;
      case 12: return DISC_3_STRIP_12;
      case 13: return DISC_3_STRIP_13;
      case 14: return DISC_3_STRIP_14;
      case 15: return DISC_3_STRIP_15;
    }
  } else if (discIndex == 4) {
    switch (stripIndex) {
      case  0: return DISC_4_STRIP_00;
      case  1: return DISC_4_STRIP_01;
      case  2: return DISC_4_STRIP_02;
      case  3: return DISC_4_STRIP_03;
      case  4: return DISC_4_STRIP_04;
      case  5: return DISC_4_STRIP_05;
      case  6: return DISC_4_STRIP_06;
      case  7: return DISC_4_STRIP_07;
      case  8: return DISC_4_STRIP_08;
      case  9: return DISC_4_STRIP_09;
      case 10: return DISC_4_STRIP_10;
      case 11: return DISC_4_STRIP_11;
      case 12: return DISC_4_STRIP_12;
      case 13: return DISC_4_STRIP_13;
      case 14: return DISC_4_STRIP_14;
      case 15: return DISC_4_STRIP_15;
    }
  } else if (discIndex == 5) {
    switch (stripIndex) {
      case  0: return DISC_5_STRIP_00;
      case  1: return DISC_5_STRIP_01;
      case  2: return DISC_5_STRIP_02;
      case  3: return DISC_5_STRIP_03;
      case  4: return DISC_5_STRIP_04;
      case  5: return DISC_5_STRIP_05;
      case  6: return DISC_5_STRIP_06;
      case  7: return DISC_5_STRIP_07;
      case  8: return DISC_5_STRIP_08;
      case  9: return DISC_5_STRIP_09;
      case 10: return DISC_5_STRIP_10;
      case 11: return DISC_5_STRIP_11;
      case 12: return DISC_5_STRIP_12;
      case 13: return DISC_5_STRIP_13;
      case 14: return DISC_5_STRIP_14;
      case 15: return DISC_5_STRIP_15;
    }
  } else if (discIndex == 6) {
    switch (stripIndex) {
      case  0: return DISC_6_STRIP_00;
      case  1: return DISC_6_STRIP_01;
      case  2: return DISC_6_STRIP_02;
      case  3: return DISC_6_STRIP_03;
      case  4: return DISC_6_STRIP_04;
      case  5: return DISC_6_STRIP_05;
      case  6: return DISC_6_STRIP_06;
      case  7: return DISC_6_STRIP_07;
      case  8: return DISC_6_STRIP_08;
      case  9: return DISC_6_STRIP_09;
      case 10: return DISC_6_STRIP_10;
      case 11: return DISC_6_STRIP_11;
      case 12: return DISC_6_STRIP_12;
      case 13: return DISC_6_STRIP_13;
      case 14: return DISC_6_STRIP_14;
      case 15: return DISC_6_STRIP_15;
    }
  } else if (discIndex == 7) {
    switch (stripIndex) {
      case  0: return DISC_7_STRIP_00;
      case  1: return DISC_7_STRIP_01;
      case  2: return DISC_7_STRIP_02;
      case  3: return DISC_7_STRIP_03;
      case  4: return DISC_7_STRIP_04;
      case  5: return DISC_7_STRIP_05;
      case  6: return DISC_7_STRIP_06;
      case  7: return DISC_7_STRIP_07;
      case  8: return DISC_7_STRIP_08;
      case  9: return DISC_7_STRIP_09;
      case 10: return DISC_7_STRIP_10;
      case 11: return DISC_7_STRIP_11;
      case 12: return DISC_7_STRIP_12;
      case 13: return DISC_7_STRIP_13;
      case 14: return DISC_7_STRIP_14;
      case 15: return DISC_7_STRIP_15;
    }
  } else {
    switch (stripIndex) {
      case  0: return DISC_8_STRIP_00;
      case  1: return DISC_8_STRIP_01;
      case  2: return DISC_8_STRIP_02;
      case  3: return DISC_8_STRIP_03;
      case  4: return DISC_8_STRIP_04;
      case  5: return DISC_8_STRIP_05;
      case  6: return DISC_8_STRIP_06;
      case  7: return DISC_8_STRIP_07;
      case  8: return DISC_8_STRIP_08;
      case  9: return DISC_8_STRIP_09;
      case 10: return DISC_8_STRIP_10;
      case 11: return DISC_8_STRIP_11;
      case 12: return DISC_8_STRIP_12;
      case 13: return DISC_8_STRIP_13;
      case 14: return DISC_8_STRIP_14;
      case 15: return DISC_8_STRIP_15;
    }
  }
}

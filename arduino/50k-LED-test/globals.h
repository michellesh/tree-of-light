#define DATA_PIN_00  2
#define DATA_PIN_01  4
#define DATA_PIN_02  5
#define DATA_PIN_03  12
#define DATA_PIN_04  13
#define DATA_PIN_05  14
#define DATA_PIN_06  18
#define DATA_PIN_07  19
#define DATA_PIN_08  21
#define DATA_PIN_09  22
#define DATA_PIN_10  23
#define DATA_PIN_11  25
#define DATA_PIN_12  26
#define DATA_PIN_13  27
#define DATA_PIN_14  32
#define DATA_PIN_15  33

#define BRIGHTNESS   255
#define COLOR_ORDER  GRB
#define LED_TYPE     WS2813

#define NUM_DISCS            9
#define NUM_STRIPS_PER_DISC  16

// LED counts were calculated by converting ft -> m
// then multiply by number of leds per meter (144)
//
//   `stripLengthFt` = length of strip (ft)
//   `metersPerFt` = 0.3048
//   `ledsPerMeter` = 144
//
//   stripLengthFt * metersPerFt * ledsPerMeter
//
// Total LEDs: 47408
#define NUM_LEDS_DISC_0  527  // 12'
#define NUM_LEDS_DISC_1  477  // 10.875'
#define NUM_LEDS_DISC_2  428  // 9.75'
#define NUM_LEDS_DISC_3  379  // 8.625'
#define NUM_LEDS_DISC_4  329  // 7.5'
#define NUM_LEDS_DISC_5  280  // 6.375'
#define NUM_LEDS_DISC_6  230  // 5.25'
#define NUM_LEDS_DISC_7  181  // 4.125'
#define NUM_LEDS_DISC_8  132  // 3'

CRGB *DISC_0_STRIP_00;
CRGB *DISC_0_STRIP_01;
CRGB *DISC_0_STRIP_02;
CRGB *DISC_0_STRIP_03;
CRGB *DISC_0_STRIP_04;
CRGB *DISC_0_STRIP_05;
CRGB *DISC_0_STRIP_06;
CRGB *DISC_0_STRIP_07;
CRGB *DISC_0_STRIP_08;
CRGB *DISC_0_STRIP_09;
CRGB *DISC_0_STRIP_10;
CRGB *DISC_0_STRIP_11;
CRGB *DISC_0_STRIP_12;
CRGB *DISC_0_STRIP_13;
CRGB *DISC_0_STRIP_14;
CRGB *DISC_0_STRIP_15;

CRGB *DISC_1_STRIP_00;
CRGB *DISC_1_STRIP_01;
CRGB *DISC_1_STRIP_02;
CRGB *DISC_1_STRIP_03;
CRGB *DISC_1_STRIP_04;
CRGB *DISC_1_STRIP_05;
CRGB *DISC_1_STRIP_06;
CRGB *DISC_1_STRIP_07;
CRGB *DISC_1_STRIP_08;
CRGB *DISC_1_STRIP_09;
CRGB *DISC_1_STRIP_10;
CRGB *DISC_1_STRIP_11;
CRGB *DISC_1_STRIP_12;
CRGB *DISC_1_STRIP_13;
CRGB *DISC_1_STRIP_14;
CRGB *DISC_1_STRIP_15;

CRGB *DISC_2_STRIP_00;
CRGB *DISC_2_STRIP_01;
CRGB *DISC_2_STRIP_02;
CRGB *DISC_2_STRIP_03;
CRGB *DISC_2_STRIP_04;
CRGB *DISC_2_STRIP_05;
CRGB *DISC_2_STRIP_06;
CRGB *DISC_2_STRIP_07;
CRGB *DISC_2_STRIP_08;
CRGB *DISC_2_STRIP_09;
CRGB *DISC_2_STRIP_10;
CRGB *DISC_2_STRIP_11;
CRGB *DISC_2_STRIP_12;
CRGB *DISC_2_STRIP_13;
CRGB *DISC_2_STRIP_14;
CRGB *DISC_2_STRIP_15;

CRGB *DISC_3_STRIP_00;
CRGB *DISC_3_STRIP_01;
CRGB *DISC_3_STRIP_02;
CRGB *DISC_3_STRIP_03;
CRGB *DISC_3_STRIP_04;
CRGB *DISC_3_STRIP_05;
CRGB *DISC_3_STRIP_06;
CRGB *DISC_3_STRIP_07;
CRGB *DISC_3_STRIP_08;
CRGB *DISC_3_STRIP_09;
CRGB *DISC_3_STRIP_10;
CRGB *DISC_3_STRIP_11;
CRGB *DISC_3_STRIP_12;
CRGB *DISC_3_STRIP_13;
CRGB *DISC_3_STRIP_14;
CRGB *DISC_3_STRIP_15;

CRGB *DISC_4_STRIP_00;
CRGB *DISC_4_STRIP_01;
CRGB *DISC_4_STRIP_02;
CRGB *DISC_4_STRIP_03;
CRGB *DISC_4_STRIP_04;
CRGB *DISC_4_STRIP_05;
CRGB *DISC_4_STRIP_06;
CRGB *DISC_4_STRIP_07;
CRGB *DISC_4_STRIP_08;
CRGB *DISC_4_STRIP_09;
CRGB *DISC_4_STRIP_10;
CRGB *DISC_4_STRIP_11;
CRGB *DISC_4_STRIP_12;
CRGB *DISC_4_STRIP_13;
CRGB *DISC_4_STRIP_14;
CRGB *DISC_4_STRIP_15;

CRGB *DISC_5_STRIP_00;
CRGB *DISC_5_STRIP_01;
CRGB *DISC_5_STRIP_02;
CRGB *DISC_5_STRIP_03;
CRGB *DISC_5_STRIP_04;
CRGB *DISC_5_STRIP_05;
CRGB *DISC_5_STRIP_06;
CRGB *DISC_5_STRIP_07;
CRGB *DISC_5_STRIP_08;
CRGB *DISC_5_STRIP_09;
CRGB *DISC_5_STRIP_10;
CRGB *DISC_5_STRIP_11;
CRGB *DISC_5_STRIP_12;
CRGB *DISC_5_STRIP_13;
CRGB *DISC_5_STRIP_14;
CRGB *DISC_5_STRIP_15;

CRGB *DISC_6_STRIP_00;
CRGB *DISC_6_STRIP_01;
CRGB *DISC_6_STRIP_02;
CRGB *DISC_6_STRIP_03;
CRGB *DISC_6_STRIP_04;
CRGB *DISC_6_STRIP_05;
CRGB *DISC_6_STRIP_06;
CRGB *DISC_6_STRIP_07;
CRGB *DISC_6_STRIP_08;
CRGB *DISC_6_STRIP_09;
CRGB *DISC_6_STRIP_10;
CRGB *DISC_6_STRIP_11;
CRGB *DISC_6_STRIP_12;
CRGB *DISC_6_STRIP_13;
CRGB *DISC_6_STRIP_14;
CRGB *DISC_6_STRIP_15;

CRGB *DISC_7_STRIP_00;
CRGB *DISC_7_STRIP_01;
CRGB *DISC_7_STRIP_02;
CRGB *DISC_7_STRIP_03;
CRGB *DISC_7_STRIP_04;
CRGB *DISC_7_STRIP_05;
CRGB *DISC_7_STRIP_06;
CRGB *DISC_7_STRIP_07;
CRGB *DISC_7_STRIP_08;
CRGB *DISC_7_STRIP_09;
CRGB *DISC_7_STRIP_10;
CRGB *DISC_7_STRIP_11;
CRGB *DISC_7_STRIP_12;
CRGB *DISC_7_STRIP_13;
CRGB *DISC_7_STRIP_14;
CRGB *DISC_7_STRIP_15;

CRGB *DISC_8_STRIP_00;
CRGB *DISC_8_STRIP_01;
CRGB *DISC_8_STRIP_02;
CRGB *DISC_8_STRIP_03;
CRGB *DISC_8_STRIP_04;
CRGB *DISC_8_STRIP_05;
CRGB *DISC_8_STRIP_06;
CRGB *DISC_8_STRIP_07;
CRGB *DISC_8_STRIP_08;
CRGB *DISC_8_STRIP_09;
CRGB *DISC_8_STRIP_10;
CRGB *DISC_8_STRIP_11;
CRGB *DISC_8_STRIP_12;
CRGB *DISC_8_STRIP_13;
CRGB *DISC_8_STRIP_14;
CRGB *DISC_8_STRIP_15;

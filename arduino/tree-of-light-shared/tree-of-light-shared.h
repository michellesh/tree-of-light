#define SLIDER_1 15  // D8
#define SLIDER_2 5   // D1
#define SLIDER_3 16  // D0
#define SLIDER_4 0   // D3

#define RED_BUTTON 2      // D4
#define BLUE_BUTTON 14    // D5
#define YELLOW_BUTTON 12  // D6
#define GREEN_BUTTON 13   // D7
#define WHITE_BUTTON 4    // D2

uint8_t senderAddress[] = {0x3C, 0x61, 0x05, 0xCF, 0xB2, 0xF7};
uint8_t receiverAddress[] = {0xAC, 0x67, 0xB2, 0xF8, 0x54, 0xF8};

char senderMacAddress[] = "3C:61:05:CF:B2:F7";
char receiverMacAddress[] = "AC:67:B2:F8:54:F8";

typedef struct msg {
  uint8_t action;
  int value;
} msg;

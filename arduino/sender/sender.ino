#include "tree-of-light-shared.h"
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <espnow.h>

#define SLIDER_1 15  // D8
#define SLIDER_2 5   // D1
#define SLIDER_3 16  // D0
#define SLIDER_4 0   // D3

#define RED_BUTTON 2      // D4
#define BLUE_BUTTON 14    // D5
#define YELLOW_BUTTON 12  // D6
#define GREEN_BUTTON 13   // D7
#define WHITE_BUTTON 4    // D2

struct Button {
  int pin;
  bool pressed;
};

struct Slider {
  int pin;
  int value;
  int prev;
};

Button redButton = {RED_BUTTON, false};
Button blueButton = {BLUE_BUTTON, false};
Button yellowButton = {YELLOW_BUTTON, false};
Button greenButton = {GREEN_BUTTON, false};
Button whiteButton = {WHITE_BUTTON, false};

Slider slider1 = {SLIDER_1};
Slider slider2 = {SLIDER_2};
Slider slider3 = {SLIDER_3};
Slider slider4 = {SLIDER_4};

msg msgRedButton = {RED_BUTTON};
msg msgBlueButton = {BLUE_BUTTON};
msg msgYellowButton = {YELLOW_BUTTON};
msg msgGreenButton = {GREEN_BUTTON};
msg msgWhiteButton = {WHITE_BUTTON};
msg msgSlider1 = {SLIDER_1};
msg msgSlider2 = {SLIDER_2};
msg msgSlider3 = {SLIDER_3};
msg msgSlider4 = {SLIDER_4};

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

  esp_now_add_peer(receiverAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(WHITE_BUTTON, INPUT_PULLUP);
  pinMode(SLIDER_1, OUTPUT);
  pinMode(SLIDER_2, OUTPUT);
  pinMode(SLIDER_3, OUTPUT);
  pinMode(SLIDER_4, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  readSliderValues();

  checkSliderChanged(slider1, msgSlider1);
  checkSliderChanged(slider2, msgSlider2);
  checkSliderChanged(slider3, msgSlider3);
  checkSliderChanged(slider4, msgSlider4);

  EVERY_N_MILLISECONDS(5) {
    checkButtonPressed(redButton, msgRedButton);
    checkButtonPressed(blueButton, msgBlueButton);
    checkButtonPressed(yellowButton, msgYellowButton);
    checkButtonPressed(greenButton, msgGreenButton);
    checkButtonPressed(whiteButton, msgWhiteButton);
  }
}

void readSliderValues() {
  static int sliderIndex = -1;
  EVERY_N_MILLISECONDS(10) {
    if (sliderIndex == -1) {
      digitalWrite(slider1.pin, HIGH);
    } else if (sliderIndex == 0) {
      slider1.value = analogRead(0);
      digitalWrite(slider1.pin, LOW);
      digitalWrite(slider2.pin, HIGH);
    } else if (sliderIndex == 1) {
      slider2.value = analogRead(0);
      digitalWrite(slider2.pin, LOW);
      digitalWrite(slider3.pin, HIGH);
    } else if (sliderIndex == 2) {
      slider3.value = analogRead(0);
      digitalWrite(slider3.pin, LOW);
      digitalWrite(slider4.pin, HIGH);
    } else if (sliderIndex == 3) {
      slider4.value = analogRead(0);
      digitalWrite(slider4.pin, LOW);
      digitalWrite(slider1.pin, HIGH);
    }
    sliderIndex = sliderIndex == 3 ? 0 : sliderIndex + 1;
  }
}

void send(msg m) { esp_now_send(0, (uint8_t *)&m, sizeof(m)); }

bool sliderValueChanged(Slider slider) {
  int BUFFER = 20;
  return slider.value < (slider.prev - BUFFER) ||
         slider.value > (slider.prev + BUFFER);
}

void checkSliderChanged(Slider &slider, msg &m) {
  if (sliderValueChanged(slider)) {
    Serial.print("Slider changed ");
    Serial.print(slider.pin);
    Serial.print(" ");
    Serial.println(slider.value);
    m.value = slider.value;
    send(m);
    slider.prev = slider.value;
  }
}

bool isButtonPressed(Button button) { return digitalRead(button.pin) == 0; }

void checkButtonPressed(Button &button, msg &m) {
  if (isButtonPressed(button)) {
    if (!button.pressed) {
      Serial.print("Button pressed ");
      Serial.println(button.pin);
      button.pressed = true;
      m.value = 1;
      send(m);
    }
  } else if (button.pressed) {
    Serial.print("Button UN-pressed ");
    Serial.println(button.pin);
    button.pressed = false;
    m.value = 0;
    send(m);
  }
}

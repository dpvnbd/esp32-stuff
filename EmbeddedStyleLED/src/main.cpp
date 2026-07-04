#include <Arduino.h>
#include "Led.hpp"
#include "Config.hpp"

Led led1 = Led(cfg::kLedPin);
uint32_t lastToggle = 0;
volatile bool buttonPressed = false;
bool blinking = true;

void IRAM_ATTR onButtonPress()
{
  buttonPressed = true;
}

void setup()
{
  Serial.begin(cfg::kBaudRate);
  led1.init();
  pinMode(cfg::kButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(cfg::kButtonPin), onButtonPress, FALLING);
}

void loop()
{
  uint32_t now = millis();

  if (blinking && (now - lastToggle >= cfg::kBlinkMs))
  {
    led1.toggle();
    lastToggle = now;
  }

  if (buttonPressed){
    buttonPressed = false;
    blinking = !blinking;
  }
}

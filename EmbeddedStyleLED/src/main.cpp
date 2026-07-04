#include <Arduino.h>
#include "Led.hpp"
#include "Config.hpp"

Led led1 = Led(cfg::kLedPin);
uint32_t lastToggle = 0;

void setup()
{
  Serial.begin(cfg::kBaudRate);
  led1.init();
}

void loop()
{
  uint32_t now = millis();

  if (now - lastToggle >= cfg::kBlinkMs){
    led1.toggle();
    lastToggle = now;
  }
}

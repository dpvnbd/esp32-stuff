#include <Arduino.h>
#include "Button.hpp"
#include "ledPatterns/Blink.hpp"
#include "ledPatterns/Chase.hpp"
#include "ledPatterns/Stop.hpp"

#define BAUD 9600
#define BOOT_PIN 0
#define BUTTON_PIN 17
#define DEBOUNCE 20

#define PRINT_PERIOD 1000
#define MODE_OFF 0
#define MODE_A 1
#define MODE_B 2

void printState();

Button bootBtn(BOOT_PIN, true, DEBOUNCE);
Button normalBtn(BUTTON_PIN, false, DEBOUNCE);
uint8_t mode = MODE_OFF;

const uint8_t ledPins[] = {2, 41, 39, 37};
uint8_t ledCount = sizeof(ledPins) / sizeof(ledPins[0]);

Stop stop(ledPins, ledCount);
Blink blink(ledPins, ledCount, 500);
Chase chase(ledPins, ledCount, 200);

LedPattern *current = &stop;

void setup()
{
  Serial.begin(BAUD);
  delay(1000);
  pinMode(BOOT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT);

  for (uint8_t i = 0; i < ledCount; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }

  printState();
}

void loop()
{
  bootBtn.update();
  normalBtn.update();

  if (bootBtn.isDown() && normalBtn.isDown())
  {
    mode = MODE_OFF;
    current = &stop;
    current->reset();
  }
  else if (bootBtn.justPressed())
  {
    mode = MODE_A;
    current = &blink;
    current->reset();
  }
  else if (normalBtn.justPressed())
  {
    mode = MODE_B;
    current = &chase;
    current->reset();
  }

  current->tick();

  printState();
}

void printState()
{
  static uint32_t lastPrint;

  if (millis() - lastPrint < PRINT_PERIOD)
  {
    return;
  }

  uint8_t bootState = bootBtn.isDown();
  uint8_t buttonState = normalBtn.isDown();

  Serial.printf("boot=%d button=%d mode=%d\n", bootState, buttonState, mode);
  lastPrint = millis();
}

#include <Arduino.h>
#include "Config.hpp"
#include "RelayState.hpp"
#include "esp_task_wdt.h"

hw_timer_t *timer;
RelayState state = RelayState::Off;
volatile bool timerElapsed = false;

void IRAM_ATTR onTimer()
{
  timerElapsed = true;
}

void enterState(RelayState s)
{
  state = s;
  uint8_t relayPinLevel;
  uint32_t newPeriod;

  if (state == RelayState::Off)
  {
    relayPinLevel = HIGH; // active low
    newPeriod = cfg::kOffPeriodSeconds;
  }
  else
  {
    relayPinLevel = LOW; // active low
    newPeriod = cfg::kOnPeriodSeconds;
  }

  digitalWrite(cfg::kRelayPin, relayPinLevel);

  timerWrite(timer, 0);
  timerAlarmWrite(timer, cfg::alarmFor(newPeriod), true);
  timerAlarmEnable(timer);

  Serial.printf("Turning %s for %u seconds\n", stateToString(state), newPeriod);
}

void setup()
{
  Serial.begin(cfg::kBaudRate);
  delay(1000);

  pinMode(cfg::kRelayPin, OUTPUT);
  timer = timerBegin(cfg::kTimerNum, cfg::kDivider, true);
  timerAttachInterrupt(timer, onTimer, true);
  timerAlarmEnable(timer);
  enterState(RelayState::On);

  esp_task_wdt_init(cfg::kWatchdogTimeoutSeconds, true);
  esp_task_wdt_add(NULL);
}

void loop()
{
  if (timerElapsed)
  {
    timerElapsed = false;
    enterState(state == RelayState::Off ? RelayState::On : RelayState::Off);

    // if(rand() < RAND_MAX / 2){
    //   delay(5000); // random hang to trigger watchdog
    // }
  }

  esp_task_wdt_reset();
}

#pragma once
#include <Arduino.h>

namespace cfg
{
    inline constexpr uint32_t kBaudRate = 115200;

    inline constexpr uint64_t kBaseFrequency = 80000000;
    inline constexpr uint16_t kDivider = 80;
    inline constexpr uint8_t kTimerNum = 0;

    inline constexpr uint32_t kTriggerPeriodSeconds = 4;                                   // 60*60 to get hour
    inline constexpr uint32_t kOnPeriodSeconds = 1;                                         // 15*60 to get 15 min
    inline constexpr uint32_t kOffPeriodSeconds = kTriggerPeriodSeconds - kOnPeriodSeconds; // remainder in off state

    constexpr uint64_t alarmFor(uint32_t periodSeconds)
    {
        return (kBaseFrequency / kDivider) * periodSeconds;
    }

    inline constexpr uint8_t kRelayPin = 4;
    inline constexpr uint8_t kWatchdogTimeoutSeconds = 3;
}

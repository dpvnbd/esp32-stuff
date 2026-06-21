#pragma once
#include <Arduino.h>
#include "LedPattern.hpp"

class Blink : public LedPattern
{
public:
    Blink(const uint8_t *pins, uint8_t count, uint32_t periodMs)
        : LedPattern(pins, count), _periodMs(periodMs) {}

    void tick() override
    {
        if (millis() - _lastUpdated < _periodMs)
        {
            return;
        }
        bool newState = !_state;

        setAll(newState ? HIGH : LOW);
        _state = newState;
        _lastUpdated = millis();
    }

private:
    uint32_t _periodMs;

    uint32_t _lastUpdated = 0;
    bool _state = false;
};

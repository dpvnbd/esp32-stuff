#pragma once
#include <Arduino.h>
#include "LedPattern.hpp"

class Chase : public LedPattern
{
public:
    Chase(const uint8_t *pins, uint8_t count, uint32_t intervalMs)
        : LedPattern(pins, count), _intervalMs(intervalMs) {}

    void tick() override
    {
        if (millis() - _lastUpdated < _intervalMs)
        {
            return;
        }

        uint8_t nextIndex = (_currentIndex + 1) % _count;
        digitalWrite(_pins[_currentIndex], LOW);
        digitalWrite(_pins[nextIndex], HIGH);
        _currentIndex = nextIndex;
        _lastUpdated = millis();
    }

    void reset() override {
        LedPattern::reset();
        _currentIndex = _count - 1;
    }

private:
    uint32_t _intervalMs;
    uint32_t _lastUpdated = 0;
    uint8_t _currentIndex = 0;
};

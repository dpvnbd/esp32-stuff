#pragma once
#include <Arduino.h>

class LedPattern
{
public:
    LedPattern(const uint8_t *pins, uint8_t count)
        : _pins(pins), _count(count) {}

    virtual void tick() = 0;

    virtual void reset()
    {
        setAll(LOW);
    }

protected:
    void setAll(uint8_t val)
    {
        for (uint8_t i = 0; i < _count; i++)
        {
            digitalWrite(_pins[i], val);
        }
    }

    const uint8_t *_pins;
    uint8_t _count;
};

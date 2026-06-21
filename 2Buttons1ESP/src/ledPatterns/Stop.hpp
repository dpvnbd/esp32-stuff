#pragma once
#include <Arduino.h>
#include "LedPattern.hpp"

class Stop : public LedPattern
{
public:
    Stop(const uint8_t *pins, uint8_t count)
        : LedPattern(pins, count) {}

    void tick() override
    {
    }
};

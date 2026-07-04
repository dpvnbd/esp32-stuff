#pragma once
#include <Arduino.h>

enum class LedState : uint8_t
{
    Off,
    On
};

class Led
{
public:
    Led(uint8_t pin)
        : pin_(pin) {}

    void init()
    {
        pinMode(pin_, OUTPUT);
        set(LedState::Off);
    }

    void set(LedState state)
    {
        state_ = state;

        uint8_t level = state_ == LedState::Off ? LOW : HIGH;
        digitalWrite(pin_, level);
    }

    LedState state() const
    {
        return state_;
    }

    void toggle()
    {
        LedState newState = state_ == LedState::Off ? LedState::On : LedState::Off;
        set(newState);
    }

private:
    uint8_t pin_;
    LedState state_ = LedState::Off;
};

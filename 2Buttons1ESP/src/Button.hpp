#pragma once
#include <Arduino.h>

class Button
{
public:
    Button(uint8_t pin, bool activeLow, uint16_t debounceMs)
        : _pin(pin), _activeLow(activeLow), _debounceMs(debounceMs) {}

    // call once per tick to calculate debounce and state
    void update()
    {
        // debounce
        bool raw = digitalRead(_pin) == (_activeLow ? LOW : HIGH);

        if (raw != _rawLast) // value changed (could be bounce)
        {
            _rawLast = raw;
            _lastChangeTime = millis(); // restart debounce timer
        }

        if (millis() - _lastChangeTime >= _debounceMs)
        {
            _stable = raw; // Held long enough, stable reading
        }

        // edge detection
        _justPressed = _stable && !_lastStable;
        _justReleased = !_stable && _lastStable;
        _lastStable = _stable;
    }

    // call any time in loop to get current state
    const bool isDown()
    {
        return _stable;
    }

    const bool justPressed()
    {
        return _justPressed;
    }

    const bool justReleased()
    {
        return _justReleased;
    }

private:
    uint8_t _pin;
    bool _activeLow;
    uint16_t _debounceMs;

    bool _rawLast = false;
    uint32_t _lastChangeTime = 0;
    bool _stable = false;
    bool _lastStable = false;

    bool _justPressed = false;
    bool _justReleased = false;
};
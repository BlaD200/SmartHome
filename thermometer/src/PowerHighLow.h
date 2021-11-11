#ifndef POWER_HIGH_LOW
#define POWER_HIGH_LOW

// TODO There should be a more lightweight header
#include <Arduino.h>

class PowerHighLow 
{
private:
    uint8_t _pin;
    bool _highFirst;

public:
    explicit PowerHighLow(uint8_t pin, bool highFirst = true) 
        : _pin(pin), _highFirst(highFirst) 
    {
        digitalWrite(_pin, _highFirst ? HIGH : LOW);
    }

    ~PowerHighLow() 
    {
        digitalWrite(_pin, _highFirst ? LOW : HIGH);
    }
};

#endif // POWER_HIGH_LOW

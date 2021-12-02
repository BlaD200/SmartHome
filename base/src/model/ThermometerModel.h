#ifndef THERMOMETER_MODEL
#define THERMOMETER_MODEL

#include "NamedType.h"

class ThermometerModel
{
private:
    const uint16_t _module_addr;
    float _temperature;
    float _humidity;

public:
    ThermometerModel(uint16_t moduleAddr):
        _module_addr(moduleAddr), _temperature(-1), _humidity(-1){};
    ThermometerModel(uint16_t moduleAddr, Temperature temperature, Humidity humidity):
        _module_addr(moduleAddr), _temperature(temperature.get()), _humidity(humidity.get()){};

    uint16_t addr() const { return _module_addr; }
    
    float getTemperature() const { return _temperature; }
    void setTemperature(float t) {
        _temperature = t;
    }
    float getHumidity() const { return _humidity; }
    int8_t setHumidity(float h) {
        if (h < 0 || h > 100)
            return -1;
        _humidity = h;
        return 0;
    }
};

#endif
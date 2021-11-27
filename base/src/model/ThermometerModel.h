#ifndef THERMOMETER_MODEL
#define THERMOMETER_MODEL

struct TemperatureParam{};
struct HumidityParam{};

using Temperature = NamedType<TemperatureParam, float>;
using Humidity = NamedType<HumidityParam, float>;

class ThermometerModel
{
private:
    const uint16_t _module_addr;
    float _temperature;
    float _humidity;

public:
    ThermometerModel(uint16_t moduleAddr, Temperature temperature = Temperature(-1), Humidity humidity = Humidity(-1)):
        _module_addr(moduleAddr), _temperature(temperature), _humidity(humidity){};

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
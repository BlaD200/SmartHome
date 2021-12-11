#ifndef THERMOMETER_MODEL
#define THERMOMETER_MODEL




#include "NamedType.h"

class ThermometerModel 
{
private:
    
    float _temperature;
    float _humidity;

public:
    ThermometerModel(){}
    ThermometerModel(Temperature temperature, Humidity humidity) 
    : _temperature(temperature.get()), _humidity(humidity.get()){}
    

    float getTemperature() const
    {
        return _temperature;
    }

    float getHumidity() const
    {
        return _humidity;
    }
};

#endif // THERMOMETER_MODEL
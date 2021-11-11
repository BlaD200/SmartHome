#ifndef THERMOMETER_MODEL
#define THERMOMETER_MODEL

#include "DHT.h"
#include "GyverPower.h"
#include "PowerHighLow.h"

class ThermometerModel 
{
private:
    DHT _dht;
    float _temperature;
    float _humidity;
    uint8_t _dhtPower;

public:
    ThermometerModel(uint8_t dhtData, uint8_t dhtType, uint8_t dhtPower) 
        : _dht(dhtData, dhtType), _dhtPower(dhtPower) 
    {
        _dht.begin();

        power.setSleepMode(POWERDOWN_SLEEP);
        power.autoCalibrate();
    }

    void readData() 
    {
        PowerHighLow powerHighLow(_dhtPower);

        power.sleep(SLEEP_2048MS);

        _humidity = _dht.readHumidity(true);
        _temperature = _dht.readTemperature();
    }

    float getTemperature() 
    {
        return _temperature;
    }

    float getHumidity() 
    {
        return _humidity;
    }
};

#endif // THERMOMETER_MODEL
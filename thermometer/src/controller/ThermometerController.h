#if !defined(THERMOMETER_CONTROLLER_H)
#define THERMOMETER_CONTROLLER_H

#include "DHT.h"
// #include "GyverPower.h"
#include "NamedType.h"
#include "PowerHighLow.h"
#include "model/ThermometerModel.h"
#include <util/delay.h>

class ThermometerController
{
private:
    DHT _dht;
    uint8_t _dhtPower;
    ThermometerModel _model;

public:
    ThermometerController(DHTData dhtData, DHTType dhtType, DHTPower dhtPower) : _dht(dhtData.get(), dhtType.get()), _dhtPower(dhtPower.get())
    {
        _dht.begin();

        // power.setSleepMode(POWERDOWN_SLEEP);
        // power.autoCalibrate();
    };

    void readData()
    {
        PowerHighLow powerHighLow(_dhtPower);

        // power.sleep(SLEEP_2048MS);
        _delay_ms(2500);

        Humidity humidity = Humidity(_dht.readHumidity(true));
        Temperature temperature = Temperature(_dht.readTemperature());
        _model = ThermometerModel(temperature, humidity);
    }

    const ThermometerModel& getModel(){
        return _model;
    }
};

#endif // THERMOMETER_CONTROLLER_H

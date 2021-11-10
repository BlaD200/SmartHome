#ifndef THERMOMETER_CONTROLLER
#define THERMOMETER_CONTROLLER

#include "Arduino.h"

#include "model\ThermometerModel.h"
#include "data.h"

class ThermometerController
{
private:
    ThermometerModel _model;
    uint16_t _last_message_id;

public:
    ThermometerController(uint8_t module_addr) : _model(module_addr){};
    ~ThermometerController(){};

    bool gotPackage(byte data[])
    {
        // return (((uint16_t)data[0] << 8) | data[1]) == _model.addr();
        return data[0] == _model.addr();
    }

    void updateData(TermometerSensorData& data)
    {
        _model.setTemperature(data.temperature);
        _model.setHumidity(data.humidity);
        _last_message_id = data.messageId;
    }

    const ThermometerModel& getModel(){
        return _model;
    }
};

#endif
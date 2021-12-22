#if !defined(MOTION_CONTROLLER_H)
#define MOTION_CONTROLLER_H

#include "Arduino.h"

#include "model\MotionModel.h"
#include "data.h"

class MotionController
{
private:
    MotionModel _model;
    uint16_t _last_message_id;
    unsigned long _last_triggered;

public:
    MotionController(uint16_t module_addr): _model(module_addr){};


    bool gotPackage(uint8_t data[])
    {
        return (((uint16_t)data[1] << 8) | data[0]) == _model.addr();
        // return data[0] == _model.addr();
    }


    bool updateData(MotionSensorData& data)
    {
        _last_message_id = data.messageId;
        if (_last_triggered == 0 || millis() - _last_triggered > 16000){
            _last_triggered = millis();
            return true;
        }

        return false;
    }
    
    const MotionModel& getModel(){
        return _model;
    }
};


#endif // MOTION_CONTROLLER_H

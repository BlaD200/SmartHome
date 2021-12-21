#ifndef TERMOMETER_SENSOR_DATA_H
#define TERMOMETER_SENSOR_DATA_H

#include "NamedType.h"

struct TermometerSensorData
{
    uint16_t radioNum;
    uint16_t messageId;
    float temperature;
    float humidity;

    TermometerSensorData() {}
    TermometerSensorData(RadioNum radioNum, MessageId messageId, Temperature temperature, Humidity humidity)
        : radioNum(radioNum.get()), messageId(messageId.get()), temperature(temperature.get()), humidity(humidity.get()){};

    String toString()
    {
        return "RADIO ID:    " + String(radioNum) + '\n' +
               "Message id:  " + String(messageId) + '\n' +
               "Temperature: " + String(temperature) + '\n' +
               "Humidity:    " + String(humidity);
    };
};

struct MotionSensorData
{
    uint16_t radioNum;
    uint16_t messageId;

    MotionSensorData(){}
    MotionSensorData(RadioNum radioNum, MessageId messageId)
        : radioNum(radioNum.get()), messageId(messageId.get()){};
    
    String toString(){
        return "RADIO ID:    " + String(radioNum) + '\n' +
               "Message id:  " + String(messageId);
    }
};


struct AlarmData
{
    uint16_t radioNum;
    uint16_t messageId;

    AlarmData(){}
    AlarmData(RadioNum radioNum, MessageId messageId)
        : radioNum(radioNum.get()), messageId(messageId.get()){};
    
    String toString(){
        return "RADIO ID:    " + String(radioNum) + '\n' +
               "Message id:  " + String(messageId);
    }
};


#endif // TERMOMETER_SENSOR_DATA_H
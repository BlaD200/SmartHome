#ifndef ARDUINO_H
    #include "Arduino.h"
#endif


struct TermometerSensorData
{
    uint8_t radioNum;
    uint8_t messageId;
    float temperature;
    float humidity;

    TermometerSensorData(){}
    TermometerSensorData(uint8_t radioNum, uint8_t messageId, float temperature, float humidity) : radioNum(radioNum), messageId(messageId), temperature(temperature), humidity(humidity)
    {
    }
};
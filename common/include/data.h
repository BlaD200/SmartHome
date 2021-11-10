#ifndef TERMOMETER_SENSOR_DATA_H
#define TERMOMETER_SENSOR_DATA_H


struct TermometerSensorData
{
    uint8_t radioNum;
    uint8_t messageId;
    float temperature;
    float humidity;

    TermometerSensorData(){}
    TermometerSensorData(uint8_t radioNum, uint8_t messageId, float temperature, float humidity) 
        :radioNum(radioNum), messageId(messageId), temperature(temperature), humidity(humidity)
    {
    };

    String toString()
    {
        return "RADIO ID:    " + String(radioNum) + '\n' +
               "Message id:  " + String(messageId) + '\n' +
               "Temperature: " + String(temperature) + '\n' +
               "Humidity:    " + String(humidity);
    };
};

#endif // TERMOMETER_SENSOR_DATA_H
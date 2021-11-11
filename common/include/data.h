#ifndef TERMOMETER_SENSOR_DATA_H
#define TERMOMETER_SENSOR_DATA_H


struct TermometerSensorData
{
    uint16_t radioNum;
    uint16_t messageId;
    float temperature;
    float humidity;

    TermometerSensorData(){}
    TermometerSensorData(uint16_t radioNum, uint16_t messageId, float temperature, float humidity) 
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
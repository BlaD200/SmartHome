#ifndef THERMOMETER_VIEW
#define THERMOMETER_VIEW

#include <util/delay.h>
#include "Gyver433.h"
#include "PowerHighLow.h"
#include "data.h"

template<typename Tx>
class ThermometerView 
{
private:
    Tx& _tx;
    uint16_t _message_id = 0;
    int8_t _radioNum;
    int8_t _radioPower;

public:
    ThermometerView(Tx& tx, int8_t radioNum, int8_t radioPower) 
        : _tx(tx), _radioNum(radioNum), _radioPower(radioPower) {}

    void sendData(float temperature, float humidity) 
    {
        PowerHighLow powerHighLow(_radioPower);
        
        _delay_ms(1);

        TermometerSensorData data(_radioNum, _message_id++, temperature, humidity);
        _tx.sendData(data);
    }
};

#endif // THERMOMETER_VIEW
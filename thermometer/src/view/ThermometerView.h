#ifndef THERMOMETER_VIEW
#define THERMOMETER_VIEW

#include <util/delay.h>
#include "Gyver433.h"
#include "PowerHighLow.h"
#include "data.h"
#include "../../utils/NamedType.h"

template<typename Tx>
class ThermometerView 
{
private:
    Tx& _tx;
    uint16_t _message_id = 0;
    int8_t _radioNum;
    int8_t _radioPower;

public:
    ThermometerView(Tx& tx, RadioNum radioNum, RadioPower radioPower) 
        : _tx(tx), _radioNum(radioNum.get()), _radioPower(radioPower.get()) {}

    void sendData(Temperature temperature, Humidity humidity) 
    {
        PowerHighLow powerHighLow(_radioPower);
        
        _delay_ms(1);

        TermometerSensorData data(RadioNum(_radioNum), MessageId(_message_id++), temperature, humidity);
        _tx.sendData(data);
    }
};

#endif // THERMOMETER_VIEW
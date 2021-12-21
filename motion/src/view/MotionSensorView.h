#if !defined(MOTION_SENSOR_VIEW_H)
#define MOTION_SENSOR_VIEW_H

#include "data.h"
#include "PowerHighLow.h"

template<typename Tx>
class MotionSensorView
{
private:
    Tx &_tx;
    uint16_t _message_id = 0;
    RadioNum _radioNum;
    // RadioPower _radioPower;
    uint32_t _time;

public:
    MotionSensorView(Tx &tx, RadioNum radioNum/* , RadioPower radioPower */)
        : _tx(tx), _radioNum(radioNum)/* , _radioPower(radioPower) */ {}

    void sendData()
    {
        MotionSensorData data(RadioNum(_radioNum), MessageId(_message_id++));      // Буфер

        /* PowerHighLow(_radioPower.get()); */
        // _delay_ms(2);                  // Немного ждем
        _tx.sendData(data);             // Отправляем пакет
        // _delay_ms(2);
    }
};

#endif // MOTION_SENSOR_VIEW_H
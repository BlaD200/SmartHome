#if !defined(MOTION_SENSOR_CONTROLLER)
#define MOTION_SENSOR_CONTROLLER

// #include "GyverPower.h"
// #include "Gyver433.h"

// #include "NamedType.h"
// #include "PowerHighLow.h"
// #include "view/MotionSensorView.h"
// #include "consts.h"

// using Tx = Gyver433_TX<RADIO_DATA, RADIO_BUF_SIZE>;
// Tx tx;
// MotionSensorView<Tx> view(tx, RadioNum(RADIO_NUM), RadioPower(RADIO_POWER));

// class MotionSensorController
// {
// private:
//     volatile bool led_on = false;
//     uint8_t send_count = 0;

// public:
//     MotionSensorController(){};

//     void loop()
//     {
//         if (!led_on)
//             power.sleep(SLEEP_FOREVER);
//         else if (led_on && send_count < 30)
//         {
//             view.sendData();
//             send_count++;

//             digitalWrite(LED_POWER, HIGH);
//             power.sleep(SLEEP_512MS);
//             digitalWrite(LED_POWER, LOW);
//         }
//         else
//         {
//             led_on = false;
//             send_count = 0;
//         }
//     }

//     void activate()
//     {
//         led_on = true;
//     }
// };

#endif // MOTION_SENSOR_CONTROLLER
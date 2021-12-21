// #define G433_SPEED 1000

#define RADIO_BUF_SIZE 8
#define RADIO_DATA PB0
// #define RADIO_POWER PB3
#define RADIO_NUM 0x03

#define PIR_DATA PB1
#define LED_POWER PB4

#include <util/delay.h>
#include <Gyver433.h>
// #include <GyverPower.h>

#include "controller/MotionSensorController.h"
// #include "view/MotionSensorView.h"
#include "data.h"
#include "PowerHighLow.h"

// MotionSensorController controller(PIR_DATA);

using Tx = Gyver433_TX<RADIO_DATA>; // If spec second param write undef var
Tx tx;
// MotionSensorView<Tx> view(tx, RadioNum(RADIO_NUM)/* , RadioPower(RADIO_POWER) */);
// Gyver433_TX<RADIO_DATA, RADIO_BUF_SIZE> tx;

volatile bool sendAlarm = false;
uint32_t _time = 0;
uint8_t send_count = 0;
uint16_t _message_id = 0;

void setup()
{
  // pinMode(RADIO_POWER, OUTPUT);
  pinMode(PIR_DATA, INPUT);
  pinMode(LED_POWER, OUTPUT);

  // power.hardwareDisable(PWR_TIMER0);
  // power.setSleepMode(POWERDOWN_SLEEP);

  PCMSK |= 1 << PCINT1;
  GIMSK |= 1 << PCIE;
  sei();

  // power.sleepDelay(30000);
}

void wakeUp();

ISR(PCINT0_vect)
{
  wakeUp();
}

void loop()
{
  // if (digitalRead(PIR_DATA))
  // {
  //   sendAlarm = true;
  //   digitalWrite(LED_POWER, HIGH);
  // }

  if (sendAlarm)
  {
    if (millis() - _time > 500)
    {
      
      if (send_count++ < 30)
      {
        // view.sendData();
        MotionSensorData data(RadioNum(RADIO_NUM), MessageId(_message_id++));
        tx.sendData(data);

        PowerHighLow(LED_POWER);
        _delay_ms(100);
        // power.sleep(SLEEP_512MS);
        
      }
      else
      {
        sendAlarm = false;
        send_count = 0;
      }

      _time = millis();
    }
  }
}

void wakeUp()
{
  sendAlarm = true;
  // digitalWrite(LED_POWER, HIGH);
}

#include <util/delay.h>
#include "Gyver433.h"
// #include "GyverPower.h"

#include "data.h"
#include "PowerHighLow.h"

#define RADIO_DATA PB1
// #define RADIO_POWER PB3
#define RADIO_BUF_SIZE 8

#define ALARM_PIN PB4
#define RECEIVED_PIN PB2

using Rx = Gyver433_RX<RADIO_DATA, RADIO_BUF_SIZE>;
Rx rx;

uint32_t time;
uint32_t lastTriggedTime = 0;
bool sendAlarm = false;
uint8_t sendCount = 30;

void setup()
{
  // pinMode(RADIO_POWER, OUTPUT);
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(RECEIVED_PIN, OUTPUT);
  digitalWrite(RECEIVED_PIN, HIGH);

  // power.hardwareDisable(PWR_ALL);
  // power.setSleepMode(POWERDOWN_SLEEP);

  PCMSK |= 1 << PCINT1;
  GIMSK |= 1 << PCIE;
  sei();
}

ISR(PCINT0_vect)
{
  rx.tickISR();
}

void loop()
{

  if (rx.gotData())
  {
    AlarmData data; // "буферная" структура
    if (rx.readData(data))
    {
      if (lastTriggedTime == 0 || millis() - lastTriggedTime > 30000) // 30 sec
      {
        sendAlarm = true;
        lastTriggedTime = millis();
        digitalWrite(RECEIVED_PIN, LOW);
        _delay_ms(100);
        digitalWrite(RECEIVED_PIN, HIGH);
      }
    }
  }

  if (sendAlarm)
  {
    if (millis() - time > 500)
    {
      if (sendCount-- > 0)
      {
        digitalWrite(ALARM_PIN, HIGH);
        // power.sleep(SLEEP_256MS);
        _delay_ms(250);
        digitalWrite(ALARM_PIN, LOW);
      }
      else
      {
        sendAlarm = false;
        sendCount = 30;
      }

      time = millis();
    }
  }
}
// #define G433_SPEED 1000

#define RADIO_BUF_SIZE 8
#define RADIO_DATA PB0
#define RADIO_POWER PB3
#define RADIO_NUM 0x03

#define PIR_DATA PB1
#define LED_POWER PB4

#include <util/delay.h>
#include <Gyver433.h>
#include <GyverPower.h>

#include "controller/MotionSensorController.h"
#include "view/MotionSensorView.h"
#include "data.h"

MotionSensorController controller;

using Tx = Gyver433_TX<RADIO_DATA, RADIO_BUF_SIZE>;
Tx tx;
MotionSensorView<Tx> view(tx, RadioNum(RADIO_NUM), RadioPower(RADIO_POWER));
// Gyver433_TX<RADIO_DATA, RADIO_BUF_SIZE> tx;


void setup()
{
  pinMode(RADIO_POWER, OUTPUT);
  pinMode(PIR_DATA, INPUT);
  pinMode(LED_POWER, OUTPUT);

  power.hardwareDisable(PWR_TIMER0);
  power.setSleepMode(POWERDOWN_SLEEP);

  PCMSK |= 1 << PCINT1;
  GIMSK |= 1 << PCIE;
  sei();

  // power.sleepDelay(30000);
}

ISR(PCINT0_vect)
{
  controller.activate();
}

void loop()
{
  controller.loop();
}
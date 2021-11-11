#define G433_SLOW 

#define DHT_DATA PB3
#define DHT_POWER PB1
#define RADIO_DATA PB0
#define RADIO_POWER PB4

#define RADIO_NUM 0x02


#include "DHT.h"
#include <util/delay.h>
#include "Gyver433.h"
#include "GyverPower.h"

#include "data.h"


DHT dht(DHT_DATA, DHT11);
Gyver433_TX<RADIO_DATA> tx;

uint16_t message_id = 0;
float h, t = 0;

void setup()
{
  pinMode(DHT_POWER, OUTPUT);
  pinMode(RADIO_POWER, OUTPUT);

  dht.begin();

  // глубокий сон
  power.setSleepMode(POWERDOWN_SLEEP); // Самый глубокий сон
  power.autoCalibrate();
}

void loop() // Main program loop
{
  digitalWrite(DHT_POWER, HIGH);
  power.sleep(SLEEP_2048MS);
  h = dht.readHumidity(true);
  t = dht.readTemperature();
  digitalWrite(DHT_POWER, LOW);

  digitalWrite(RADIO_POWER, HIGH);
  _delay_ms(1);
  TermometerSensorData data(RADIO_NUM, message_id++, t, h);
  tx.sendData(data);
  digitalWrite(RADIO_POWER, LOW);

  power.sleep(SLEEP_4096MS);
}
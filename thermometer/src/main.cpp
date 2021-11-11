#define G433_SLOW 

#define DHT_DATA PB3
#define DHT_TYPE DHT11
#define DHT_POWER PB1

#define RADIO_DATA PB0
#define RADIO_NUM 0x02
#define RADIO_POWER PB4

#include "model/ThermometerModel.h"
#include "view/ThermometerView.h"

ThermometerModel model(DHT_DATA, DHT_TYPE, DHT_POWER);

using Tx = Gyver433_TX<RADIO_DATA>;
Tx tx;
ThermometerView<Tx> view(tx, RADIO_NUM, RADIO_POWER);

void setup()
{
  pinMode(DHT_POWER, OUTPUT);
  pinMode(RADIO_POWER, OUTPUT);
}

void loop()
{
  model.readData();

  view.sendData(model.getTemperature(), model.getHumidity());

  power.sleep(SLEEP_4096MS);
}

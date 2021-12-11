#define G433_SLOW 

#define DHT_DATA PB3
#define DHT_TYPE DHT11
#define DHT_POWER PB1

#define RADIO_DATA PB0
#define RADIO_NUM 0x02
#define RADIO_POWER PB4

#include "model/ThermometerModel.h"
#include "view/ThermometerView.h"

ThermometerModel model(DHTData(DHT_DATA), DHTType(DHT_TYPE), DHTPower(DHT_POWER));

using Tx = Gyver433_TX<RADIO_DATA>;
Tx tx;
ThermometerView<Tx> view(tx, RadioNum(RADIO_NUM), RadioPower(RADIO_POWER));

void setup()
{
  pinMode(DHT_POWER, OUTPUT);
  pinMode(RADIO_POWER, OUTPUT);
}

void loop()
{
  model.readData();

  view.sendData(Temperature(model.getTemperature()), Humidity(model.getHumidity()));

  power.sleep(SLEEP_4096MS);
}

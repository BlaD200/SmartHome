// #define G433_SLOW

#define DHT_DATA PB3
#define DHT_TYPE DHT11
#define DHT_POWER PB1

#define RADIO_DATA PB0
#define RADIO_NUM 0x02
#define RADIO_POWER PB4

#include "controller/ThermometerController.h"
#include "view/ThermometerView.h"

ThermometerController controller(DHTData(DHT_DATA), DHTType(DHT_TYPE), DHTPower(DHT_POWER));

using Tx = Gyver433_TX<RADIO_DATA>;
Tx tx;
ThermometerView<Tx> view(tx, RadioNum(RADIO_NUM), RadioPower(RADIO_POWER));

unsigned long time;

void setup()
{
    pinMode(DHT_POWER, OUTPUT);
    pinMode(RADIO_POWER, OUTPUT);
}

void loop()
{
    if (millis() - time > 4000)
    {
        controller.readData();

        view.sendData(
            Temperature(controller.getModel().getTemperature()),
            Humidity(controller.getModel().getHumidity()));

        time = millis();
    }

    // power.sleep(SLEEP_4096MS);
}

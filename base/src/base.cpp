#include "GyverButton.h"
#include <Gyver433.h>
#include "SoftwareSerial.h"

#include "base.h"
#include "controller\ThermometerController.h"
#include "controller\MotionController.h"
#include "view\ThermometerView.h"
#include "view\AlertAndroidView.h"

Gyver433_TX<12> tx;
Gyver433_RX<2, 20> rx;

SoftwareSerial EspSerial(10, 11);

ThermometerController therm(0x02);
ThermometerConsoleView therm_view(therm.getModel());
ThermometerAndroidView therm_and_view(therm.getModel(), EspSerial);

MotionController motion(0x03);
AlertAndroidView alert_view(motion.getModel(), EspSerial);

uint32_t time;
uint32_t flash_time;
float temp;
float hum;

unsigned long startTime;
bool ledStatus = false;
bool receivedAnswer = true;

const uint16_t RADIO_NUM = 11;

void isr();

void setupTransmitter()
{
    // initialize wireless driver
    Serial.begin(9600);

    EspSerial.begin(4800);
    // transmitterDriver.init();
    startTime = millis();
    attachInterrupt(0, isr, CHANGE);
    Serial.println("Transmitter inited.");
}

void isr()
{
    rx.tickISR();
}

void transmitterLoop()
{
    // if (millis() - flash_time > 1000)
    // {
    //     flash_time = millis();
    //     EspSerial.write("5.0|28.9;");
    // }
    // if (Serial.available()){
    //     char str[30];
    //     EspSerial.write(Serial.readBytesUntil(';', str, 30));
    //     EspSerial.readBytesUntil()
    // }

    // if (EspSerial.available()) {
    //     char str[30];
    //     int len = EspSerial.readBytesUntil(';', str, 30);
    //     str[len] = 0;
    //     Serial.write(str);
    // }

    if (rx.gotData())
    {
        if (therm.gotPackage(rx.buffer))
        {
            TermometerSensorData data;
            if (rx.readData(data))
            {
                therm.updateData(data);
                Serial.println(data.toString());
                therm_view.updateView();
                therm_and_view.updateView();
            }
            else
            {
                Serial.println("Wrong data");
            }
        }
        else if (motion.gotPackage(rx.buffer))
        {
            MotionSensorData data;
            if (rx.readData(data))
            {
                if (motion.updateData(data))
                {
                    Serial.println("Motion detected!");
                    Serial.println(data.toString());
                    Serial.println();
                    alert_view.updateView();
                }
            }
            else
            {
                Serial.println("Wrong data");
            }
        }
        else
        {
            Serial.print("Unknown device signature: ");
            Serial.println(((uint16_t)rx.buffer[0] << 8) | rx.buffer[1]);
        }
    }
}
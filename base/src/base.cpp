#define BTN_ON_PIN 3 // кнопка подключена сюда (BTN_PIN --- КНОПКА --- GND)
#define BTN_OFF_PIN 4

//#define G433_SPEED 1000   // скорость 100-10000 бит/с, по умолч. 2000 бит/с
#define G433_SLOW // отправляю раз в секунду на SYN480R

#include "GyverButton.h"
#include <Gyver433.h>

#include "base.h"
#include "controller\ThermometerController.h"
#include "view\ThermometerView.h"

Gyver433_TX<12> tx;    // указали пин
Gyver433_RX<2, 20> rx; // указали пин и размер буфера

GButton onBtn(BTN_ON_PIN);
GButton offBtn(BTN_OFF_PIN);

ThermometerController therm(0x02);
ThermometerConsoleView therm_view(therm.getModel());


uint32_t time;
unsigned long startTime;
bool isBtnClicked = false;
bool ledStatus = false;
bool receivedAnswer = true;

const uint8_t RADIO_NUM = 11;

const uint8_t ON_MESSAGE[] = {0x55};  // binary 0101 0101
const uint8_t OFF_MESSAGE[] = {0x96}; // binary 1001 0110
const uint8_t RECEIVED_MESSAGE[] = {0x01};

void isr();

void setupTransmitter()
{
    // initialize wireless driver
    Serial.begin(9600);
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
    onBtn.tick();
    offBtn.tick();

    if (onBtn.isClick())
    {
        Serial.println("ON");
        ledStatus = true;
        isBtnClicked = true;
    }
    if (offBtn.isClick())
    {
        Serial.println("OFF");
        ledStatus = false;
        isBtnClicked = true;
    }

    // if (isBtnClicked || !receivedAnswer)
    // {
    //     digitalWrite(LED_BUILTIN, ledStatus);

    //     if (millis() - startTime > 1000)
    //     {
    //         Serial.println("sending...");

    //         data.messageId++;          // тут счётчик
    //         data.radioNum = RADIO_NUM; // случайное число

    //         if (ledStatus)
    //         {
    //             data.message = *ON_MESSAGE;
    //         }
    //         else
    //         {
    //             data.message = *OFF_MESSAGE;
    //         }

    //         // detachInterrupt(0);
    //         tx.sendData(data);
    //         // attachInterrupt(0, isr, CHANGE);

    //         Serial.println("Transmitted:");
    //         Serial.println(data.messageId);
    //         Serial.println(data.radioNum);
    //         Serial.println(data.message);
    //         Serial.println();

    //         startTime = millis();
    //     }

    //     receivedAnswer = false;
    //     isBtnClicked = false;
    // }

    if (rx.gotData())
    { // если больше 0

        if (therm.gotPackage(rx.buffer))
        {
            TermometerSensorData dataAnswer;
            if (rx.readData(dataAnswer))
            { 

                therm.updateData(dataAnswer);
                Serial.println(dataAnswer.toString());
                therm_view.updateView();

                // if ((dataAnswer.messageId == data.messageId) && (dataAnswer.message == *RECEIVED_MESSAGE))
                // {
                //     receivedAnswer = true;
                // }
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
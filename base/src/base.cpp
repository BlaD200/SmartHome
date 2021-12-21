#define BTN_ON_PIN 3
#define BTN_OFF_PIN 4

#include "GyverButton.h"
#include <Gyver433.h>

#include "base.h"
#include "controller\ThermometerController.h"
#include "view\ThermometerView.h"

Gyver433_TX<12> tx;
Gyver433_RX<2, 20> rx;

GButton onBtn(BTN_ON_PIN);
GButton offBtn(BTN_OFF_PIN);

ThermometerController therm(0x02);
ThermometerConsoleView therm_view(therm.getModel());


uint32_t time;
unsigned long startTime;
bool isBtnClicked = false;
bool ledStatus = false;
bool receivedAnswer = true;

const uint16_t RADIO_NUM = 11;

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

    if (rx.gotData())
    {
        if (therm.gotPackage(rx.buffer))
        {
            TermometerSensorData dataAnswer;
            if (rx.readData(dataAnswer))
            { 
                therm.updateData(dataAnswer);
                Serial.println(dataAnswer.toString());
                therm_view.updateView();
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
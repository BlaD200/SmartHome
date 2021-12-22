#if !defined(THERMOMETER_VIEW)
#define THERMOMETER_VIEW

#include "Arduino.h"

#include "view\BaseView.h"
#include "model\ThermometerModel.h"

class ThermometerConsoleView : public BaseView<ThermometerModel>
{
private:
    /* data */

protected:
    void _updateView() override
    {
        Serial.println("Addr: " + String(_model.addr()));
        Serial.print("T: ");
        Serial.println(_model.getTemperature());
        Serial.print("H: ");
        Serial.println(_model.getHumidity());
        Serial.println();
    }

public:
    ThermometerConsoleView(const ThermometerModel& model): BaseView(model){};
    ~ThermometerConsoleView(){};
};

class ThermometerAndroidView : public BaseView<ThermometerModel>
{
private:
    SoftwareSerial& _serial;

protected:
    void _updateView() override
    {
        _serial.println(String(_model.getTemperature()) + "|" + String(_model.getHumidity()) + ";");
    }

public:
    ThermometerAndroidView(const ThermometerModel& model, SoftwareSerial& serial): BaseView(model), _serial(serial){};
    ~ThermometerAndroidView(){};
};

#endif // THERMOMETER_VIEW

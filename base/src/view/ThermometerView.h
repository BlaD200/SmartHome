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
    ThermometerConsoleView(ThermometerModel model): BaseView(model){};
    ~ThermometerConsoleView(){};
};

#endif // THERMOMETER_VIEW

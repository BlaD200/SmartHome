#if !defined(ALERT_ANDROID_VIEW_H)
#define ALERT_ANDROID_VIEW_H

#include "Arduino.h"
#include "SoftwareSerial.h"

#include "view\BaseView.h"
#include "model\MotionModel.h"

class AlertAndroidView : public BaseView<MotionModel>
{
private:
    SoftwareSerial& _serial;
protected:
    void _updateView() override
    {
        _serial.println("alert;");
    }

public:
    AlertAndroidView(const MotionModel& model, SoftwareSerial& serial): BaseView(model), _serial(serial){};
    ~AlertAndroidView(){};
};


#endif // ALERT_ANDROID_VIEW_H

#if !defined(MOTION_MODEL_H)
#define MOTION_MODEL_H

#include "Arduino.h"

#include "data.h"

class MotionModel
{
private:
    uint16_t _module_addr;
public:
    MotionModel(uint16_t module_addr): _module_addr(module_addr){};

    uint16_t addr() const {return _module_addr;}
};


#endif // MOTION_MODEL_H

//
// Created by troy on 12/6/16.
//

#ifndef WEEK2_SENSOR_H
#define WEEK2_SENSOR_H

#include "TSensor.hpp"

class BoolSensor: public TSensor<bool> {
public:
    BoolSensor(bool value);
    bool IsTrue(void);
    bool IsFalse(void);
};


#endif //WEEK2_SENSOR_H

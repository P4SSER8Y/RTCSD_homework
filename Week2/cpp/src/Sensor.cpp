//
// Created by troy on 12/6/16.
//

#include "Sensor.h"

BoolSensor::BoolSensor(bool value = true) : TSensor(value) {
}

bool BoolSensor::IsTrue(void) {
    return this->value;
}

bool BoolSensor::IsFalse(void) {
    return !this->value;
}


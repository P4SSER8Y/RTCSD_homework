//
// Created by troy on 12/6/16.
//

#pragma once

#ifndef WEEK2_TSENSOR_HPP
#define WEEK2_TSENSOR_HPP


template <typename T>
class TSensor {
protected:
    T value;

public:
    TSensor(){}
    TSensor(T value) {
        this->Set(value);
    }
    void Set(T value) {
        this->value = value;
    }
    T Get(void) {
        return this->value;
    }
};


#endif //WEEK2_TSENSOR_HPP

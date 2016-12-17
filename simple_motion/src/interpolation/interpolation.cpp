//
// Created by troy on 12/12/16.
//

#include <iostream>
#include "interpolation.h"

Interpolation::Interpolation() {
    this->status = kIntNotYetConfigured;
    this->type = "unkown";
    std::cerr << "initial interpolation" << std::endl;
}

Interpolation::~Interpolation() {
    std::cerr << "destroy interpolation" << std::endl;
}

std::string Interpolation::get_type() {
    return this->type;
}

InterpolationState Interpolation::start(const TimeInS now,
                                        const double start_position,
                                        const double start_velocity) {}

InterpolationState Interpolation::move(const TimeInS now) {}

InterpolationState Interpolation::get_status() {}

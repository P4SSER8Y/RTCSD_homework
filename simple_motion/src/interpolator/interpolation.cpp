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

InterpolationState Interpolation::start(const RTIME start_time_ns) {}

InterpolationState Interpolation::move(const RTIME curr_time_ns) {}

InterpolationState Interpolation::get_status() {}

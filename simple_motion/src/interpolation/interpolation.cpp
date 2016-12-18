//
// Created by troy on 12/12/16.
//

#include "interpolation.h"

#include <stdexcept>

Interpolation::Interpolation() {
    this->status = kIntNotYetConfigured;
    this->type = "unkown";
}

Interpolation::~Interpolation() {}

std::string Interpolation::get_type() {
    return this->type;
}

InterpolationState Interpolation::get_status() {
    return this->status;
}

double Interpolation::get_position(void) {
    return this->p;
}

double Interpolation::get_velocity(void) {
    return this->v;
}

double Interpolation::get_acceleration(void) {
    return this->a;
}

double Interpolation::get_jerk(void) {
    return this->j;
}

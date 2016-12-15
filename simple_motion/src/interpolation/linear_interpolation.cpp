//
// Created by troy on 12/15/16.
//

#include "linear_interpolation.h"

#include <iostream>
#include <iomanip>
#include <include/global_variables.h>

#include "global_variables.h"

LinearInterpolation::LinearInterpolation() {
    this->type = "linear interpolation";
    std::cerr << "initial linear interpolation" << std::endl;
}

LinearInterpolation::~LinearInterpolation() {
    std::cerr << "destroy linear interpolation" << std::endl;
}

InterpolationState LinearInterpolation::check() {
    interpolate_state = kIntIdle;
    return kIntIdle;
}

InterpolationState LinearInterpolation::get_status() {
    return this->interpolate_state;
}

std::string LinearInterpolation::get_type() {
    return this->type;
}

InterpolationState LinearInterpolation::start(const RTIME start_time_ns) {
    if (this->check() != kIntIdle)
        return kIntIdle;

    double now = start_time_ns / 1e9;
    t0 = now;
    s0 = *axis;

    t1 = t0 + (position - axis->position) / velocity;
    s1.position = position;
    s1.velocity = 0;

    std::cerr << "start @" << std::setiosflags(std::ios::fixed) << t0 << std::endl <<
              "stop @" << t1 << std::endl;
    std::cerr << "switch to state <Acc>" << std::endl;

    state = kRunning;
    return kIntIdle;
}

InterpolationState LinearInterpolation::move(const RTIME curr_time_ns) {
    double now = curr_time_ns / 1e9;
    if (now >= t1) {
        axis->position = s1.position;
        axis->velocity = s1.velocity;
        return kIntDone;
    } else {
        axis->position = s0.position + this->velocity * (now - t0);
        axis->velocity = this->velocity;
        return kIntRunning;
    }
}

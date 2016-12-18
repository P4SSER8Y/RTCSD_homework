//
// Created by troy on 12/15/16.
//

#include "linear_interpolation.h"

#include <iostream>
#include <iomanip>

LinearInterpolation::LinearInterpolation() {
    this->type = "linear interpolation";
}

LinearInterpolation::~LinearInterpolation() {}

InterpolationState LinearInterpolation::check() {
    interpolate_state = kIntIdle;
    return kIntIdle;
}

InterpolationState LinearInterpolation::start(const TimeInS now,
                                              const double start_position,
                                              const double start_velocity) {
    if (this->check() != kIntIdle)
        return kIntIdle;

    this->p = start_position;
    this->v = start_velocity;
    this->a = 0;
    this->j = 0;

    t0 = now;
    s0.position = start_position;
    s0.velocity = start_velocity;

    t1 = t0 + (position - this->p) / velocity;
    s1.position = position;
    s1.velocity = 0;

    std::cerr << "start @" << std::setiosflags(std::ios::fixed) << t0 << std::endl <<
              "stop @" << t1 << std::endl;
    std::cerr << "switch to state <Moving>" << std::endl;

    state = kRunning;
    return kIntIdle;
}

InterpolationState LinearInterpolation::move(const TimeInS now) {
    if (now >= t1) {
        this->p = s1.position;
        this->v = s1.velocity;
        state = kEnd;
        return kIntDone;
    } else {
        this->p = s0.position + this->velocity * (now - t0);
        this->v = this->velocity;
        return kIntRunning;
    }
}

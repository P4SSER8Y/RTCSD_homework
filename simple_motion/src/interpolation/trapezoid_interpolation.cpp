//
// Created by troy on 12/13/16.
//

#include "trapezoid_interpolation.h"

#include <iostream>
#include <stdexcept>
#include <include/global_variables.h>
#include <iomanip>

#include "global_variables.h"

TrapezoidInterpolation::TrapezoidInterpolation() {
    this->type = "trapezoid interpolation";
    std::cerr << "initial trapezoid interpolation" << std::endl;
}

TrapezoidInterpolation::~TrapezoidInterpolation() {
    std::cerr << "destroy trapezoid interpolation" << std::endl;
}

InterpolationState TrapezoidInterpolation::check() {
    return kIntIdle;
}

InterpolationState TrapezoidInterpolation::get_status() {
    interpolate_state = kIntIdle;
    return this->interpolate_state;
}

std::string TrapezoidInterpolation::get_type() {
    return this->type;
}

InterpolationState TrapezoidInterpolation::start(const RTIME start_time_ns) {
    if (this->check() != kIntIdle)
        return kIntIdle;

    double now = start_time_ns / 1e9;
    state = kAcceleration;
    t0 = now;
    s0 = *axis;

    t1 = t0 + velocity / acceleration;
    s1.position = s0.position + velocity * velocity / (2 * acceleration);
    s1.velocity = velocity;

    t2 = t1 + (position - s0.position) / velocity
         - velocity / (2 * acceleration)
         - velocity / (2 * deceleration);
    s2.position = s1.position + velocity * (t2 - t1);
    s2.velocity = velocity;

    t3 = t2 + velocity / deceleration;
    s3.position = position;
    s3.velocity = 0;

    std::cerr << "start @" << std::setiosflags(std::ios::fixed) << t0 << std::endl <<
              "acc until " << t1 << std::endl <<
              "dec @" << t2 << std::endl <<
              "stop @" << t3 << std::endl;
    std::cerr << "switch to state <Acc>" << std::endl;
    return kIntIdle;
}

InterpolationState TrapezoidInterpolation::move(const RTIME curr_time_ns) {
//    if ((this->interpolate_state != kIntRunning) || (this->interpolate_state != kIntIdle))
//        return this->interpolate_state;

    double now = curr_time_ns / 1e9;
    switch (this->state) {
        case kAcceleration:
            if (now >= t1) {
                axis->velocity = s1.velocity;
                axis->position = s1.position;
                state = kLinear;
                // No Break; Linear Uniform Moving at once
                std::cerr << "switch to state <Linear>" << std::endl;
            } else {
                axis->velocity = this->velocity * (now - t0) / (t1 - t0);
                axis->position = s0.position + 0.5 * this->acceleration * (now - t0) * (now - t0);
                return kIntRunning;
            }
            // Linear Uniform Moving
        case kLinear:
            if (now >= t2) {
                axis->position = s2.position;
                axis->velocity = s2.velocity;
                state = kDeceleration;
                // No Break; Decelerating at once
                std::cerr << "switch to state <Dec>" << std::endl;
            } else {
                axis->position = s1.position + s1.velocity * (now - t1);
                axis->velocity = this->velocity;
                return kIntRunning;
            }
        case kDeceleration:
            if (now >= t3) {
                axis->position = s3.position;
                axis->velocity = s3.velocity;
                state = kEnd;
                // No Break; Stop at once
                std::cerr << "switch to state <End>" << std::endl;
            } else {
                axis->velocity = s2.velocity - this->deceleration * (now - t2);
                axis->position = s2.position + s2.velocity * (now - t2)
                                 - 0.5 * this->deceleration * (now - t2) * (now - t2);
                return kIntRunning;
            }
        case kEnd:
            return kIntDone;
        default:
            std::cerr << "WTF" << std::endl;
            return kIntError;
    }
}

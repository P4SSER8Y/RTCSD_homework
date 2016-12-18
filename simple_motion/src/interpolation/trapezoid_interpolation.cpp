//
// Created by troy on 12/13/16.
//

#include "trapezoid_interpolation.h"

#include <iostream>
#include <stdexcept>
#include <iomanip>

TrapezoidInterpolation::TrapezoidInterpolation() {
    this->type = "trapezoid interpolation";
}

TrapezoidInterpolation::~TrapezoidInterpolation() {}

InterpolationState TrapezoidInterpolation::check() {
    interpolate_state = kIntIdle;
    return kIntIdle;
}

InterpolationState TrapezoidInterpolation::start(const TimeInS now,
                                                 const double start_position,
                                                 const double start_velocity) {
    if (this->check() != kIntIdle)
        return kIntIdle;

    this->p = start_position;
    this->v = start_velocity;
    this->j = 0;

    state = kAcceleration;
    t0 = now;
    s0.position = start_position;
    s0.velocity = start_velocity;
    s0.acceleration = acceleration;

    t1 = t0 + velocity / acceleration;
    s1.position = s0.position + velocity * velocity / (2 * acceleration);
    s1.velocity = velocity;
    s1.acceleration = 0;

    t2 = t1 + (position - s0.position) / velocity
         - velocity / (2 * acceleration)
         - velocity / (2 * deceleration);
    s2.position = s1.position + velocity * (t2 - t1);
    s2.velocity = velocity;
    s2.acceleration = deceleration;

    t3 = t2 + velocity / deceleration;
    s3.position = position;
    s3.velocity = 0;
    s3.acceleration = 0;

    std::cerr << "start @" << std::setiosflags(std::ios::fixed) << t0 << std::endl <<
              "acc until " << t1 << std::endl <<
              "dec @" << t2 << std::endl <<
              "stop @" << t3 << std::endl;
    std::cerr << "switch to state <Acc>" << std::endl;
    return kIntIdle;
}

InterpolationState TrapezoidInterpolation::move(const TimeInS now) {

    switch (this->state) {
        case kAcceleration:
            if (now >= t1) {
                this->p = s1.position;
                this->v = s1.velocity;
                this->a = s1.acceleration;
                state = kLinear;
                // No Break; Linear Uniform Moving at once
                std::cerr << "switch to state <Linear>" << std::endl;
            } else {
                this->p = s0.position + 0.5 * this->acceleration * (now - t0) * (now - t0);
                this->v = this->velocity * (now - t0) / (t1 - t0);
                this->a = s0.acceleration;
                return kIntRunning;
            }
            // Linear Uniform Moving
        case kLinear:
            if (now >= t2) {
                this->p = s2.position;
                this->v = s2.velocity;
                this->a = s2.acceleration;
                state = kDeceleration;
                // No Break; Decelerating at once
                std::cerr << "switch to state <Dec>" << std::endl;
            } else {
                this->p = s1.position + s1.velocity * (now - t1);
                this->v = this->velocity;
                this->a = s1.acceleration;
                return kIntRunning;
            }
        case kDeceleration:
            if (now >= t3) {
                this->p = s3.position;
                this->v = s3.velocity;
                this->a = s3.acceleration;
                state = kEnd;
                // No Break; Stop at once
                std::cerr << "switch to state <End>" << std::endl;
            } else {
                this->p = s2.position + s2.velocity * (now - t2)
                          - 0.5 * this->deceleration * (now - t2) * (now - t2);
                this->v = s2.velocity - this->deceleration * (now - t2);
                this->a = s2.acceleration;
                return kIntRunning;
            }
        case kEnd:
            return kIntDone;
        default:
            std::cerr << "WTF" << std::endl;
            return kIntError;
    }
}

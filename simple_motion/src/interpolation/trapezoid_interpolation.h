//
// Created by troy on 12/13/16.
//

#pragma once

#ifndef SIMPLE_MOTION_TRAPEZOID_INTERPOLATION_H
#define SIMPLE_MOTION_TRAPEZOID_INTERPOLATION_H

#include "interpolation.h"

class TrapezoidInterpolation final : public Interpolation {
private:
    InterpolationState interpolate_state;
    std::string type;
    enum {
        kIdle, kAcceleration, kLinear, kDeceleration, kEnd
    } state = kIdle;

    double t0, t1, t2, t3;
    struct {
        double position;
        double velocity;
        double acceleration;
    } s0, s1, s2, s3;

public:
    double position;
    double velocity;
    double acceleration;
    double deceleration;

    TrapezoidInterpolation();

    virtual ~TrapezoidInterpolation();

    virtual InterpolationState check(void);

    /**
     * @brief Start Interpolation, it'll check the validation of the command
     * @param now t0 in second
     * @return current interpolating status, only kError/kRunning
     */
    virtual InterpolationState start(const TimeInS now,
                                     const double start_position,
                                     const double start_velocity);

    /**
     * @brief interpolate once
     * @param now t in second
     * @return current interpolating status
     */
    virtual InterpolationState move(const TimeInS now);
};


#endif //SIMPLE_MOTION_TRAPEZOID_INTERPOLATION_H

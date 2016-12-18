//
// Created by troy on 12/15/16.
//

#ifndef SIMPLE_MOTION_LINEAR_INTERPOLATION_H
#define SIMPLE_MOTION_LINEAR_INTERPOLATION_H

#include "interpolation.h"

class LinearInterpolation final : public Interpolation {
private:
    InterpolationState interpolate_state;
    std::string type;
    enum {
        kIdle, kRunning, kEnd
    } state = kIdle;

    double t0, t1;
    struct {
        double position;
        double velocity;
    } s0, s1;

public:
    double position;
    double velocity;

    LinearInterpolation();

    virtual ~LinearInterpolation();

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


#endif //SIMPLE_MOTION_LINEAR_INTERPOLATION_H

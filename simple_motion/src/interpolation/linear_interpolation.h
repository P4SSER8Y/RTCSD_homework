//
// Created by troy on 12/15/16.
//

#ifndef SIMPLE_MOTION_LINEAR_INTERPOLATION_H
#define SIMPLE_MOTION_LINEAR_INTERPOLATION_H

#include "interpolation.h"
#include "global_variables.h"

class LinearInterpolation : public Interpolation {
private:
    InterpolationState interpolate_state;
    std::string type;
    enum {
        kIdle, kRunning, kEnd
    } state = kIdle;

    double t0, t1;
    AxisStatus s0, s1;

public:
    double position;
    double velocity;
    AxisStatus *axis;

    LinearInterpolation();

    virtual ~LinearInterpolation();

    virtual InterpolationState check(void);

    /**
     * @brief Start Interpolation, it'll check the validation of the command
     * @param start_time_ns t0 in nanosecond
     * @return current interpolating status, only kError/kRunning
     */
    virtual InterpolationState start(const RTIME start_time_ns);

    /**
     * @brief interpolate once
     * @param curr_time_ns t in nanosecond
     * @return current interpolating status
     */
    virtual InterpolationState move(const RTIME curr_time_ns);

    /**
     * @brief return current interpolating status
     * @return interpolating status
     */
    virtual InterpolationState get_status(void);

    virtual std::string get_type(void);
};


#endif //SIMPLE_MOTION_LINEAR_INTERPOLATION_H

//
// Created by troy on 12/12/16.
//

#pragma once

#ifndef SIMPLE_MOTION_INTERPOLATION_H
#define SIMPLE_MOTION_INTERPOLATION_H

#include <string>
#include "native/types.h"
#include "native/timer.h"

enum InterpolationState {
    kIntNotYetConfigured,
    kIntIdle,
    kIntRunning,
    kIntDone,
    kIntError,
};

class Interpolation {
private:
    InterpolationState status;
    std::string type;
public:

    /**
     * @brief Constructor with no parameter
     */
    Interpolation();

    ~Interpolation();

//    virtual InterpolationState check(void);

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


#endif //SIMPLE_MOTION_INTERPOLATION_H

//
// Created by troy on 12/12/16.
//

#pragma once

#ifndef SIMPLE_MOTION_INTERPOLATION_H
#define SIMPLE_MOTION_INTERPOLATION_H

#include <string>

typedef double TimeInS;

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
    double p;
    double v;
    double a;
    double j;

    /**
     * @brief Constructor with no parameter
     */
    Interpolation();

    virtual ~Interpolation();

//    virtual InterpolationState check(void);

    /**
     * @brief Start Interpolation, it'll check the validation of the command
     * @param start_time_ns t0 in nanosecond
     * @param start_position start position
     * @param start_velocity start velocity
     * @return current interpolating status, only kError/kRunning
     */
    virtual InterpolationState start(const TimeInS now,
                                     const double start_position,
                                     const double start_velocity);

    /**
     * @brief interpolate once
     * @param curr_time_ns t in nanosecond
     * @return current interpolating status
     */
    virtual InterpolationState move(const TimeInS now);

    /**
     * @brief return current interpolating status
     * @return interpolating status
     */
    virtual InterpolationState get_status(void);

    virtual std::string get_type(void);
};


#endif //SIMPLE_MOTION_INTERPOLATION_H

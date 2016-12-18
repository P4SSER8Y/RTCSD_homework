//
// Created by troy on 12/12/16.
//

#pragma once

#ifndef SIMPLE_MOTION_INTERPOLATION_H
#define SIMPLE_MOTION_INTERPOLATION_H

#include <string>

typedef double TimeInS;

/**
 * Interpolation state
 */
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

protected:
    double p;
    double v;
    double a;
    double j;

    /**
     * @brief Not allow create instance
     */
    Interpolation();

public:
    virtual ~Interpolation();

    /**
     * @param start_position start position
     * @param start_velocity start velocity
     * @return current interpolating status, only kError/kRunning
     */
    virtual InterpolationState start(const TimeInS now,
                                     const double start_position,
                                     const double start_velocity) = 0;

    /**
     * @brief interpolate once (pure virtual function)
     * @param TimeInS current time stamp
     * @return current interpolating status
     */
    virtual InterpolationState move(const TimeInS now) = 0;

    /**
     * @brief return current interpolating status
     * @return interpolating status
     */
    virtual InterpolationState get_status(void);

    /**
     * @brief return the type of this interpolation
     * @return the type of this interpolation
     */
    std::string get_type(void);

    /**
     * @brief return the position
     * @return the position
     */
    double get_position(void);

    /**
     * @brief return the velocity
     * @return the velocity
     */
    double get_velocity(void);

    /**
     * @brief return the acceleration
     * @return the acceleration
     */
    double get_acceleration(void);

    /**
     * @brief return the jerk
     * @return the jerk
     */
    double get_jerk(void);
};


#endif //SIMPLE_MOTION_INTERPOLATION_H

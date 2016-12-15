//
// Created by troy on 12/10/16.
//

#pragma once

#ifndef SIMPLE_MOTION_PROGRAM_CONSTANTS_H
#define SIMPLE_MOTION_PROGRAM_CONSTANTS_H

#include "native/types.h"
#include "native/queue.h"
#include "native/event.h"

/**
 * @brief Axis Status
 */
typedef struct {
    double position;
    double velocity;
} AxisStatus;

extern bool terminated;

extern const RTIME RT_TIME_FREQ;
extern const double INTERPOLATION_PERIOD;
extern AxisStatus axis_1;


extern RT_EVENT event_command;
namespace event_command_mask {
    const unsigned long kNone = 0x0;
    const unsigned long kRequest = 0x01;
    const unsigned long kDone = 0x02;
    const unsigned long kError = 0x80000000;
    const unsigned long kAny= 0xffffffff;
}

extern RT_QUEUE queue_command;

/**
 * @brief Initialize non-const variables
 */
void init_global_variables(void);

/**
 * @brief Delete all variables
 */
void delete_global_variables(void);

#endif //SIMPLE_MOTION_PROGRAM_CONSTANTS_H

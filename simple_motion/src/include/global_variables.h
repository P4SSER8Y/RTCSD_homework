//
// Created by troy on 12/10/16.
//

#pragma once

#ifndef SIMPLE_MOTION_PROGRAM_CONSTANTS_H
#define SIMPLE_MOTION_PROGRAM_CONSTANTS_H

#include "native/types.h"
#include "motion_types.h"

extern const RTIME RT_TIME_FREQ;
extern const double INTERPOLATION_PERIOD;
extern tAxisSetpoint axis1;
extern tPosCmd new_cmd;

/**
 * @brief Initialize non-const variables
 */
void init_global_variables(void);

#endif //SIMPLE_MOTION_PROGRAM_CONSTANTS_H

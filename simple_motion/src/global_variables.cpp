//
// Created by troy on 12/10/16.
//

#include "global_variables.h"

#include <native/types.h>
#include <motion_types.h>

const double INTERPOLATION_PERIOD = 0.001;
const RTIME RT_TIME_FREQ = 1000000000;
tAxisSetpoint axis1;
tPosCmd new_cmd;

void init_global_variables() {
    axis1.Position = 20000;
    new_cmd.Request = false;
    new_cmd.Response = false;
    new_cmd.Done = 0;
}

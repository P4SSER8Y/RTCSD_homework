//
// Created by troy on 12/10/16.
//

#include "global_variables.h"


const double INTERPOLATION_PERIOD = 0.001;
const RTIME RT_TIME_FREQ = 1000000000;
AxisStatus axis_1;
tPosCmd new_cmd;

RT_EVENT event_command;

bool terminated;

void init_global_variables() {
    axis_1.Position = 20000;
    terminated = false;

    rt_event_create(&event_command, "event", event_command_mask::kNone, EV_FIFO);
}

void delete_global_variables() {
    rt_event_delete(&event_command);
}

//
// Created by troy on 12/10/16.
//

#include "global_variables.h"

#include <memory>
#include <include/global_variables.h>

#include "interpolation/interpolation.h"

const double INTERPOLATION_PERIOD = 0.001;
const RTIME RT_TIME_FREQ = 1000000000;
AxisStatus axis_x, axis_y;

RT_QUEUE queue_axis_x, queue_axis_y;
RT_EVENT event_command;

bool terminated;

/**
 * @brief Initialize global variables
 */
void init_global_variables() {
    axis_x.position = 0;
    axis_x.velocity = 0;
    strcpy(axis_x.name, "axis X");

    axis_y.position = 0;
    axis_y.velocity = 0;
    strcpy(axis_y.name, "axis Y");
    terminated = false;

    rt_queue_create(&queue_axis_x, "axis X", 64 * sizeof(Interpolation *), 64, Q_FIFO | Q_SHARED);
    rt_queue_create(&queue_axis_y, "axis Y", 64 * sizeof(Interpolation *), 64, Q_FIFO | Q_SHARED);
    rt_event_create(&event_command, "event: command", event_command_mask::kNone, EV_FIFO);
}

/**
 * @brief release allocated spaces
 */
void delete_global_variables() {
    rt_event_delete(&event_command);
    rt_queue_delete(&queue_axis_x);
    rt_queue_delete(&queue_axis_y);
}

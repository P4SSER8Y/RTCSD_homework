//
// Created by troy on 12/10/16.
//

#include "global_variables.h"

#include <memory>

#include "interpolation/interpolation.h"

const double INTERPOLATION_PERIOD = 0.001;
const RTIME RT_TIME_FREQ = 1000000000;
AxisStatus axis_1;

RT_QUEUE queue_command;
RT_EVENT event_command;

bool terminated;

/**
 * @brief Initialize global variables
 */
void init_global_variables() {
    axis_1.position = 20000;
    axis_1.velocity = 0;
    terminated = false;

    rt_queue_create(&queue_command, "queue: command", 64 * sizeof(Interpolation *), 64,
                    Q_FIFO | Q_SHARED);
    rt_event_create(&event_command, "event: command", event_command_mask::kNone, EV_FIFO);
}

/**
 * @brief release allocated spaces
 */
void delete_global_variables() {
    rt_event_delete(&event_command);
    rt_queue_delete(&queue_command);
}

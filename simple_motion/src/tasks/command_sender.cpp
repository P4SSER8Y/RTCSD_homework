//
// Created by troy on 12/10/16.
//

#include "command_sender.h"

#include <native/task.h>

#include "global_variables.h"
#include "interpolation/interpolation.h"
#include "interpolation/trapezoid_interpolation.h"
#include "interpolation/linear_interpolation.h"

namespace task {
    namespace command_sender {
        static int cycle_count = 0;

        void main(void *arg) {
            int err;
            unsigned long event_flag;
            rt_task_set_periodic(NULL, TM_NOW, 2000000000);

            while (1) {
                rt_task_wait_period(NULL);

                cycle_count = cycle_count + 1;

                if (cycle_count == 2) {
                    auto new_cmd = (TrapezoidInterpolation **) rt_queue_alloc(&queue_axis_x,
                                                                              sizeof(Interpolation *));
                    *new_cmd = new TrapezoidInterpolation();
                    (*new_cmd)->position = 60000;
                    (*new_cmd)->velocity = 5000;
                    (*new_cmd)->acceleration = 500;
                    (*new_cmd)->deceleration = 500;
                    (*new_cmd)->axis = &axis_x;
                    rt_queue_send(&queue_axis_x,
                                  new_cmd,
                                  sizeof(Interpolation *),
                                  Q_NORMAL);
                } else if (cycle_count == 1) {
                    auto new_cmd = (TrapezoidInterpolation **) rt_queue_alloc(&queue_axis_y,
                                                                              sizeof(Interpolation *));
                    *new_cmd = new TrapezoidInterpolation();
                    (*new_cmd)->position = -60000;
                    (*new_cmd)->velocity = -5000;
                    (*new_cmd)->acceleration = -5000;
                    (*new_cmd)->deceleration = -5000;
                    (*new_cmd)->axis = &axis_y;
                    rt_queue_send(&queue_axis_y,
                                  new_cmd,
                                  sizeof(Interpolation *),
                                  Q_NORMAL);
//                } else if (cycle_count == 2) {
//                    auto new_cmd = (LinearInterpolation **) rt_queue_alloc(&queue_axis_y,
//                                                                           sizeof(Interpolation *));
//                    *new_cmd = new LinearInterpolation();
//                    (*new_cmd)->position = 2000;
//                    (*new_cmd)->velocity = 5000;
//                    (*new_cmd)->axis = &axis_y;
//                    rt_queue_send(&queue_axis_y,
//                                  new_cmd,
//                                  sizeof(Interpolation *),
//                                  Q_NORMAL);
                } else {
                    err = rt_event_wait(&event_command,
                                        event_command_mask::kDone,
                                        &event_flag,
                                        EV_ANY,
                                        TM_INFINITE);
                    err = rt_event_clear(&event_command, event_command_mask::kDone, &event_flag);
                    err = rt_event_wait(&event_command,
                                        event_command_mask::kDone,
                                        &event_flag,
                                        EV_ANY,
                                        TM_INFINITE);
                    err = rt_event_clear(&event_command, event_command_mask::kDone, &event_flag);
                    err = rt_event_wait(&event_command,
                                        event_command_mask::kDone,
                                        &event_flag,
                                        EV_ANY,
                                        TM_INFINITE);
                    terminated = true;
                }
            }
        }
    }
}


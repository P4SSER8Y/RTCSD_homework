//
// Created by troy on 12/10/16.
//

#include "command_sender.h"

#include <native/task.h>

#include "global_variables.h"
#include "interpolation/interpolation.h"
#include "interpolation/trapezoid_interpolation.h"

namespace task {
    namespace command_sender {
        static int cycle_count = 0;

        void main(void *arg) {
            int err;
            TrapezoidInterpolation **new_cmd;
            unsigned long event_flag;
            rt_task_set_periodic(NULL, TM_NOW, 2000000000);

            while (1) {
                rt_task_wait_period(NULL);

                cycle_count = cycle_count + 1;

                if (cycle_count == 1) {
                    new_cmd = (TrapezoidInterpolation **) rt_queue_alloc(&queue_command,
                                                                         sizeof(Interpolation *));
                    *new_cmd = new TrapezoidInterpolation();
                    (*new_cmd)->position = 200000;
                    (*new_cmd)->velocity = 5000;
                    (*new_cmd)->acceleration = 500;
                    (*new_cmd)->deceleration = 500;
                    (*new_cmd)->axis = &axis_1;
                    rt_queue_send(&queue_command,
                                  new_cmd,
                                  sizeof(Interpolation *),
                                  Q_NORMAL);

                    rt_event_signal(&event_command, event_command_mask::kRequest);

                } else if (cycle_count == 2) {
                    new_cmd = (TrapezoidInterpolation **) rt_queue_alloc(&queue_command,
                                                                         sizeof(Interpolation *));
                    *new_cmd = new TrapezoidInterpolation();
                    (*new_cmd)->position = 0;
                    (*new_cmd)->velocity = -5000;
                    (*new_cmd)->acceleration = -500;
                    (*new_cmd)->deceleration = -500;
                    (*new_cmd)->axis = &axis_1;
                    rt_queue_send(&queue_command,
                                  new_cmd,
                                  sizeof(Interpolation *),
                                  Q_NORMAL);

                    rt_event_signal(&event_command, event_command_mask::kRequest);
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
                    terminated = true;
                }
            }
        }
    }
}


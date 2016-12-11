//
// Created by troy on 12/10/16.
//

#include "command_sender.h"

#include <native/task.h>
#include <global_variables.h>

namespace task {
    namespace command_sender{
        static int cycle_count = 0;

        void main(void *arg)
        {
            int err;
            TrajectoryParameters *new_cmd;
            unsigned long event_flag;
            rt_task_set_periodic(NULL, TM_NOW, 2000000000);

            while (1) {
                rt_task_wait_period(NULL);

                cycle_count = cycle_count + 1;

                if(cycle_count == 1)
                {
                    new_cmd = (TrajectoryParameters *) rt_queue_alloc(&queue_command, sizeof(TrajectoryParameters));
                    new_cmd->Position = 200000;
                    new_cmd->Velocity = 1000;
                    new_cmd->Acceleration = 50;
                    new_cmd->Deceleration = 50;
                    new_cmd->Jerk = 0;
                    rt_queue_send(&queue_command, new_cmd, sizeof(TrajectoryParameters), Q_NORMAL);


                    rt_event_signal(&event_command, event_command_mask::kRequest);

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


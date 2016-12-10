//
// Created by troy on 12/10/16.
//


#include <native/task.h>
#include <global_variables.h>

namespace task {
    namespace command_sender{
        static int cycle_count = 0;

        void main(void *arg)
        {
            rt_task_set_periodic(NULL, TM_NOW, 2000000000);

            new_cmd.Request = false;
            new_cmd.Response = false;
            new_cmd.Done = false;
            new_cmd.Position = 0;
            new_cmd.Velocity = 0;
            new_cmd.Acceleration = 0;
            new_cmd.Deceleration = 0;
            new_cmd.Jerk = 0;

            while (1) {
                rt_task_wait_period(NULL);

                cycle_count = cycle_count + 1;

                if(cycle_count == 1)
                {
                    new_cmd.Request = true;
                    new_cmd.Response = false;
                    new_cmd.Done = false;
                    new_cmd.Position = 200000;
                    new_cmd.Velocity = 1000;
                    new_cmd.Acceleration = 50;
                    new_cmd.Deceleration = 50;
                    new_cmd.Jerk = 0;
                }
            }
        }
    }
}


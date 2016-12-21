#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>

#include <rtdk.h>
#include <native/task.h>

#include "global_variables.h"
#include "all_tasks.h"

RT_TASK task_trajectory_generator_x;
RT_TASK task_trajectory_generator_y;
RT_TASK task_command_sender;
RT_TASK task_debug;


void catch_signal(int sig)
{
    std::cerr << "Catch signal " << sig << std::endl;
    terminated = true;
}

void init_tasks(void) {
    /* Avoids memory swapping for this program */
    mlockall(MCL_CURRENT|MCL_FUTURE);

    rt_printf("A simple motion control demo\n");
    rt_task_create(&task_trajectory_generator_x, "rttask_trajectory_generator_x", 0, 95, 0);
    rt_task_create(&task_trajectory_generator_y, "rttask_trajectory_generator_y", 0, 95, 0);
    rt_task_create(&task_command_sender, "rttask_command_sender", 0, 92, 0);
    rt_task_create(&task_debug, "rttask_debug", 0, 90, 0);

    rt_task_start(&task_trajectory_generator_x, &task::trajectory_generator::main, (void *) &axis_x);
    rt_task_start(&task_trajectory_generator_y, &task::trajectory_generator::main, (void *) &axis_y);
    rt_task_start(&task_command_sender, &task::command_sender::main, NULL);
    rt_task_start(&task_debug, &task::debug::main, NULL);
}

void delete_tasks(void) {
    rt_task_delete(&task_trajectory_generator_x);
    rt_task_delete(&task_trajectory_generator_y);
    rt_task_delete(&task_command_sender);
    rt_task_delete(&task_debug);
}

void join_tasks(void) {
}

int main(int argc, char* argv[])
{
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);

    rt_print_auto_init(1);
    init_global_variables();
    init_tasks();

    int cnt = 0;
    while (!terminated) {
        sleep(1);
        rt_printf("tick: %d\n", ++cnt);
    }
    printf("End! \n");

    join_tasks();
    delete_tasks();
    delete_global_variables();

    return 0;
}

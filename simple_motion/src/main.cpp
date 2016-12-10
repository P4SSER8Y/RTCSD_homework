#include "motion_types.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>

#include "global_variables.h"
#include "all_tasks.h"

//Global variables

RT_TASK task_trajectory_generator;
RT_TASK task_command_sender;
RT_TASK task_debug;


void catch_signal(int sig)
{
}

void init_tasks(void) {
    /* Avoids memory swapping for this program */
    mlockall(MCL_CURRENT|MCL_FUTURE);

    printf("A simple motion control demo\n");
    rt_task_create(&task_trajectory_generator, "rttask_trajectory_generator", 0, 90, 0);
    rt_task_create(&task_command_sender, "rttask_command_sender", 0, 92, 0);
    rt_task_create(&task_debug, "rttask_debug", 0, 95, 0);

    rt_task_start(&task_trajectory_generator, &task::trajectory_generator::main, NULL);
    rt_task_start(&task_command_sender, &task::command_sender::main, NULL);
    rt_task_start(&task_debug, &task::debug::main, NULL);
}

int main(int argc, char* argv[])
{
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);

    init_global_variables();
    init_tasks();

    int cnt = 0;
    while (!new_cmd.Done) {
        sleep(1);
        printf("tick: %d\n", ++cnt);
    }
    printf("End! \n");
    rt_task_delete(&task_trajectory_generator);
    rt_task_delete(&task_command_sender);
    rt_task_delete(&task_debug);
    return 0;
}

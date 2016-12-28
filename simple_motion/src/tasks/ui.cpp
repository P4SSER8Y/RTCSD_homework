//
// Created by troy on 12/17/16.
//

#include "ui.h"

#include <native/task.h>
#include <native/pipe.h>
#include <native/timer.h>

#include <rtdk.h>
#include <iostream>

#include "global_variables.h"

namespace task {
    namespace ui {
        void main(void *arg) {
            rt_printf("task_ui entered\n");
            rt_task_set_periodic(NULL, TM_NOW, 1e9);

            RT_PIPE pipe;
            rt_pipe_bind(&pipe, "simple_motion_ui", TM_INFINITE);
            while (1) {
                char ch;
                rt_pipe_read(&pipe, &ch, sizeof(ch), TM_INFINITE);
                rt_printf("cmd: %c\n", ch);
            }
        }
    }
}
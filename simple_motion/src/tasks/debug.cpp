//
// Created by troy on 12/10/16.
//

#include "debug.h"

#include <iomanip>
#include <fstream>

#include "native/task.h"
#include "native/timer.h"

#include "global_variables.h"

namespace task {
    namespace debug {
        void main(void *arg) {
            rt_task_set_periodic(NULL, TM_NOW, (RTIME) (RT_TIME_FREQ * 0.1));

            std::ofstream log{"debug.log"};

            printf("Task Debug Init\n");
            while (1) {
                rt_task_wait_period(NULL);
                auto curr = axis_1;
                auto now = rt_timer_read() / (double) RT_TIME_FREQ;
                log << std::setiosflags(std::ios::fixed) << now << '\t' << curr.Position << '\t' << curr.Velocity
                    << std::endl;
                log.flush();
            }
        }
    }
}
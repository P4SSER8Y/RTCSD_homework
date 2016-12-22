//
// Created by troy on 12/10/16.
//

#include "print_to_files.h"

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

    while (1) {
        rt_task_wait_period(NULL);
        auto curr_x = axis_x;
        auto curr_y = axis_y;
        auto now = rt_timer_read() / (double) RT_TIME_FREQ;
        log << std::setiosflags(std::ios::fixed) << now << '\t'
            << curr_x.position << '\t' << curr_x.velocity << '\t'
            << curr_y.position << '\t' << curr_y.velocity << '\t'
            << std::endl;
        log.flush();
    }
}

}
}
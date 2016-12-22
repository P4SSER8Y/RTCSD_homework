//
// Created by troy on 12/10/16.
//

#include "trajectory_generator.h"

#include <iostream>
#include <stdexcept>
#include <include/global_variables.h>

#include <rtdk.h>
#include "native/task.h"
#include "native/timer.h"

#include "interpolation/interpolation.h"


namespace task {
namespace trajectory_generator {

void main(void *arg) {
    rt_task_set_periodic(NULL, TM_NOW, (RTIME) (RT_TIME_FREQ * INTERPOLATION_PERIOD));

    enum TaskState {
        kTaskIdle, kTaskRunning, kTaskEnd, kTaskError
    };

    TaskState state = kTaskIdle;

    auto axis = (AxisStatus *) arg;
    RT_QUEUE queue_command;
    rt_queue_bind(&queue_command, axis->name, TM_INFINITE);

    Interpolation *interpolation = nullptr;

    while (1) {
        rt_task_wait_period(NULL);
        auto now = rt_timer_read();
        switch (state) {
            case kTaskIdle:
                void *msg;
                rt_queue_receive(&queue_command, &msg, TM_INFINITE);
                memcpy(&interpolation, msg, sizeof(Interpolation *));
                rt_queue_free(&queue_command, msg);

                std::cerr << "Receive command: " << interpolation->get_type() << std::endl;

                if (interpolation->start(rt_timer_read() / 1e9,
                                         axis->position,
                                         axis->velocity) == kIntIdle)
                    state = kTaskRunning;
                else {
                    state = kTaskError;
                    std::cerr << "Error occurred\nProgram paused" << std::endl;
                    break;
                }
            case kTaskRunning: {
                auto ret = interpolation->move(now / 1e9);
                axis->position = interpolation->get_position();
                axis->velocity = interpolation->get_velocity();
                switch (ret) {
                    case kIntError:
                        state = kTaskError;
                        std::cerr << "Error occurred" << std::endl;
                        break;
                    case kIntRunning:
                        break;
                    case kIntDone:
                        state = kTaskEnd;
                        break;
                    default:
                        state = kTaskError;
                        std::cerr << "unknown state" << std::endl;
                        break;
                }
            }
                break;
            case kTaskEnd:
                state = kTaskIdle;
                delete (interpolation);
                rt_event_signal(&event_command,
                                event_command_mask::kDone);
                break;
            case kTaskError:
                break;
        }
    }
}

}
}
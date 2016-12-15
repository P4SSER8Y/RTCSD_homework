//
// Created by troy on 12/10/16.
//

#include "trajectory_generator.h"

#include <iostream>
#include <memory>
#include <stdexcept>

#include "native/task.h"
#include "native/timer.h"

#include "global_variables.h"
#include "interpolator/interpolation.h"


namespace task {
    namespace trajectory_generator {
        void main(void *arg) {
            int err;
            unsigned long event_flag;

            rt_task_set_periodic(NULL, TM_NOW, (RTIME) (RT_TIME_FREQ * INTERPOLATION_PERIOD));

            enum TaskState {
                kTaskIdle, kTaskRunning, kTaskEnd, kTaskError
            };

            TaskState state = kTaskIdle;

            std::shared_ptr<Interpolation> interpolation;

            while (1) {
                rt_task_wait_period(NULL);
                auto now = rt_timer_read();
                switch (state) {
                    case kTaskIdle:
                        err = rt_event_wait(&event_command,
                                            event_command_mask::kRequest,
                                            &event_flag,
                                            EV_ANY,
                                            TM_INFINITE);
                        rt_event_clear(&event_command, event_command_mask::kRequest, &event_flag);

                        void *msg;
                        rt_queue_receive(&queue_command, &msg, TM_INFINITE);
                        memcpy(&interpolation, msg, sizeof(std::shared_ptr<Interpolation>));
                        rt_queue_free(&queue_command, msg);

                        if (interpolation->start(rt_timer_read()) == kIntIdle)
                            state = kTaskRunning;
                        else {
                            state = kTaskError;
                            std::cerr << "Error occurred\nProgram paused" << std::endl;
                            break;
                        }
                    case kTaskRunning:
                        switch (interpolation->move(now)) {
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
                        break;
                    case kTaskEnd:
                        state = kTaskIdle;
                        interpolation.reset();
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
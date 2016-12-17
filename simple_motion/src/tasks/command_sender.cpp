//
// Created by troy on 12/10/16.
//

#include "command_sender.h"

#include <native/task.h>

#include "global_variables.h"
#include "interpolation/interpolation.h"
#include "interpolation/trapezoid_interpolation.h"
#include "interpolation/linear_interpolation.h"

namespace task {
    namespace command_sender {
        int send_command_linear(RT_QUEUE &queue,
                                const double position,
                                const double velocity) {
            auto new_cmd = (LinearInterpolation **) rt_queue_alloc(&queue, sizeof(Interpolation *));
            *new_cmd = new LinearInterpolation();
            (*new_cmd)->position = position;
            (*new_cmd)->velocity = velocity;

            return rt_queue_send(&queue,
                                 new_cmd,
                                 sizeof(Interpolation *),
                                 Q_NORMAL);
        }

        int send_command_trapezoid(RT_QUEUE &queue,
                                   const double position,
                                   const double velocity,
                                   const double acceleration,
                                   const double deceleration) {

            auto new_cmd = (TrapezoidInterpolation **) rt_queue_alloc(&queue, sizeof(Interpolation *));
            *new_cmd = new TrapezoidInterpolation();
            (*new_cmd)->position = position;
            (*new_cmd)->velocity = velocity;
            (*new_cmd)->acceleration = acceleration;
            (*new_cmd)->deceleration = deceleration;
            return rt_queue_send(&queue,
                                 new_cmd,
                                 sizeof(Interpolation *),
                                 Q_NORMAL);
        }

        void main(void *arg) {
            send_command_trapezoid(queue_axis_x, 6e4, 5e3, 5e2, 5e2);
            send_command_linear(queue_axis_y, 13200, 300);
            send_command_trapezoid(queue_axis_x, 0, -5e3, -5e2, -5e2);
        }
    }
}

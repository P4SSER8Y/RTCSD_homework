//
// Created by troy on 12/10/16.
//

#include <iostream>
#include <stdexcept>

#include "native/task.h"
#include "native/timer.h"

#include "motion_types.h"
#include "global_variables.h"


namespace task {
    namespace trajectory_generator {
        void main(void *arg) {
            static double now{0}, t0{0}, t1{0}, t2{0}, t3{0};
            static tAxisSetpoint s0{0, 0}, s1{0, 0}, s2{0, 0}, s3{0, 0};

            rt_task_set_periodic(NULL, TM_NOW, (RTIME)(RT_TIME_FREQ * INTERPOLATION_PERIOD));

            tPosCmd target;
            enum Interpolation_State {
                Idle, Acc, Uniform, Dec, End
            };

            Interpolation_State state = Idle;

            while (1) {
                rt_task_wait_period(NULL);
                now = rt_timer_read() / (double) RT_TIME_FREQ;

                switch (state) {
                    // Waiting for command
                    case Idle:
                        if (new_cmd.Request) {
                            target = new_cmd;
                            new_cmd.Request = false;
                            state = Acc;
                            t0 = now;
                            s0 = axis1;

                            t1 = t0 + target.Velocity / target.Acceleration;
                            s1.Position = s0.Position + target.Velocity * target.Velocity / (2 * target.Acceleration);
                            s1.Velocity = target.Velocity;

                            t2 = t1 + (target.Position - axis1.Position) / target.Velocity
                                 - target.Velocity / (2 * target.Acceleration)
                                 - target.Velocity / (2 * target.Deceleration);
                            s2.Position = s1.Position + target.Velocity * (t2 - t1);
                            s2.Velocity = target.Velocity;

                            t3 = t2 + target.Velocity / target.Deceleration;
                            s3.Position = target.Position;
                            s3.Velocity = 0;
                            std::cerr << "switch to state <Acc>" << std::endl;
                            // No Break; accelerate at once
                        } else {
                            break;
                        }

                        // Accelerating
                    case Acc:
                        if (now >= t1) {
                            axis1.Velocity = s1.Velocity;
                            axis1.Position = s1.Position;
                            state = Uniform;
                            // No Break; Linear Uniform Moving at once
                            std::cerr << "switch to state <Uniform>" << std::endl;
                        } else {
                            axis1.Velocity = target.Velocity * (now - t0) / (t1 - t0);
                            axis1.Position = s0.Position + 0.5 * target.Acceleration * (now - t0) * (now - t0);
                            break;
                        }

                        // Linear Uniform Moving
                    case Uniform:
                        if (now >= t2) {
                            axis1.Position = s2.Position;
                            axis1.Velocity = s2.Velocity;
                            state = Dec;
                            // No Break; Decelerating at once
                            std::cerr << "switch to state <Dec>" << std::endl;
                        } else {
                            axis1.Velocity = target.Velocity;
                            axis1.Position = s1.Position + s1.Velocity * (now - t1);
                            break;
                        }

                        // Decelerating
                    case Dec:
                        if (now >= t3) {
                            axis1.Position = s3.Position;
                            axis1.Velocity = s3.Velocity;
                            state = End;
                            // No Break; Stop at once
                            std::cerr << "switch to state <End>" << std::endl;
                        } else {
                            axis1.Velocity = s2.Velocity - target.Deceleration * (now - t2);
                            axis1.Position = s2.Position + s2.Velocity * (now - t2)
                                             - 0.5 * target.Deceleration * (now - t2) * (now - t2);
                            break;
                        }

                        // Stop
                    case End:
                        new_cmd.Done = true;
                        state = Idle;
                        std::cerr << "switch to state <Idle>" << std::endl;
                        break;

                        // Should not reach here
                    default:
                        throw new std::runtime_error("Reach Unknown State");
                }

            }
        }
    }
}
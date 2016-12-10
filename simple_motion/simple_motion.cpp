#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/timer.h>

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <iomanip>


// Data Type

typedef struct
{
    bool Request;
    bool Response;
    bool Done;
    double Position;
    double Velocity;
    double Acceleration;
    double Deceleration;
    double Jerk;
} tPosCmd;

typedef struct
{
    double Position;
    double Velocity;
} tAxisSetpoint;

//Global variables

RT_TASK task_trajectory_generator;
RT_TASK task_command_sender;
RT_TASK task_debug;

tPosCmd new_cmd;
tAxisSetpoint axis1;

const double INTERPOLATION_PERIOD = 0.001;
const RTIME RT_TIME_FREQ = 1000000000;

const RTIME PROGRAM_START_TIME = rt_timer_read();

int cycle_count = 0;



void task_trajectory_generator_proc(void *arg) {
    static double now{0}, t0{0}, t1{0}, t2{0}, t3{0};
    static tAxisSetpoint s0{0, 0}, s1{0, 0}, s2{0, 0}, s3{0, 0};

//	rt_task_set_periodic(NULL, TM_NOW, (RTIME)(RT_TIME_FREQ * INTERPOLATION_PERIOD));
    rt_task_set_periodic(NULL, TM_NOW, 100000000);

    axis1.Position = 0;
    axis1.Velocity = 0;

    tPosCmd target;
    enum Interpolation_State {Idle, Acc, Uniform, Dec, End};

    Interpolation_State state = Idle;

    while (1) {
        rt_task_wait_period(NULL);
        now = rt_timer_read() / (double) RT_TIME_FREQ;

        switch (state) {
            // Waiting for command
            case Idle:
                if (new_cmd.Request){
                    target = new_cmd;
                    new_cmd.Request = false;
                    state = Acc;
                    t0 = now;
                    s0 = axis1;

                    t1 = t0 + target.Velocity / target.Acceleration;
                    s1.Position = s0.Position + target.Velocity * target.Velocity / (2 * target.Acceleration);
                    s1.Velocity = target.Velocity;

                    t2 = t1 +  (target.Position - axis1.Position) / target.Velocity
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

void task_command_sender_proc(void *arg)
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

/**
 * @brief print the current position & velocity to debug.log every 0.1s
 * @param arg
 */
void task_debug_proc(void *arg) {
    rt_task_set_periodic(NULL, TM_NOW, (RTIME) (RT_TIME_FREQ * 0.1));

    std::ofstream log{"debug.log"};

    printf("Task Debug Init\n");
    while(1) {
        rt_task_wait_period(NULL);
        auto curr = axis1;
        auto now = rt_timer_read() / (double) RT_TIME_FREQ;
//		printf("%0.6f\t%0.6f\t%0.6f\n", now, curr.Position, curr.Velocity);
        log << std::setiosflags(std::ios::fixed) << now << '\t' << curr.Position << '\t' << curr.Velocity << std::endl;
        log.flush();
    }
}

void catch_signal(int sig)
{
}


int main(int argc, char* argv[])
{
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);

    /* Avoids memory swapping for this program */
    mlockall(MCL_CURRENT|MCL_FUTURE);

    printf("A simple motion control demo\n");
    /*
     * Arguments: &task,
     *            name,
     *            stack size (0=default),
     *            priority,
     *            mode (FPU, start suspended, ...)
     */
    rt_task_create(&task_trajectory_generator, "rttask_trajectory_generator", 0, 90, 0);
    rt_task_create(&task_command_sender, "rttask_command_sender", 0, 92, 0);
    rt_task_create(&task_debug, "rttask_debug", 0, 95, 0);

    /*
     * Arguments: &task,
     *            task function,
     *            function argument
     */
    rt_task_start(&task_trajectory_generator, &task_trajectory_generator_proc, NULL);
    rt_task_start(&task_command_sender, &task_command_sender_proc, NULL);
    rt_task_start(&task_debug, &task_debug_proc, NULL);

//    pause();
    int cnt = 0;
    while (!new_cmd.Done) {
        rt_timer_spin(1000000000);
        printf("tick: %d\n", ++cnt);
    }
    printf("End! \n");
    rt_task_delete(&task_trajectory_generator);
    rt_task_delete(&task_command_sender);
    rt_task_delete(&task_debug);
    return 0;
}

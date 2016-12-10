//
// Created by troy on 12/10/16.
//

#pragma once

#ifndef SIMPLE_MOTION_TASK_DEBUG_H
#define SIMPLE_MOTION_TASK_DEBUG_H

namespace task {
    namespace debug {
        /**
         * @brief print the current position & velocity to debug.log every 0.1s
         * @param arg
         */
        void main(void *arg);
    }
}

#endif //SIMPLE_MOTION_TASK_DEBUG_H

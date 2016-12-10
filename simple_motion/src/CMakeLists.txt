AUX_SOURCE_DIRECTORY(. SRC_CODES)
SET(ALL_TASKS
        tasks/task_trajectory_generator.cpp
        tasks/task_command_sender.cpp
        tasks/task_debug.cpp
        )

ADD_EXECUTABLE(simple_motion ${SRC_CODES} ${ALL_TASKS})

INCLUDE_DIRECTORIES(./include)

TARGET_LINK_LIBRARIES(simple_motion native xenomai pthread rt)

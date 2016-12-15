AUX_SOURCE_DIRECTORY(. SRC_CODES)
SET(ALL_TASKS
        tasks/trajectory_generator.cpp
        tasks/command_sender.cpp
        tasks/debug.cpp
        )

ADD_EXECUTABLE(simple_motion ${SRC_CODES} ${ALL_TASKS})

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./include)

ADD_SUBDIRECTORY(interpolator)

TARGET_LINK_LIBRARIES(simple_motion interpolator)
TARGET_LINK_LIBRARIES(simple_motion native xenomai pthread rt)

SET(ALL_TASKS
        tasks/trajectory_generator.cpp
        tasks/command_sender.cpp
        tasks/print_to_files.cpp
        )

ADD_EXECUTABLE(simple_motion main.cpp global_variables.cpp ${ALL_TASKS})

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./include)

ADD_SUBDIRECTORY(interpolation)

TARGET_LINK_LIBRARIES(simple_motion interpolation)
TARGET_LINK_LIBRARIES(simple_motion native xenomai pthread rt)

SET(ALL_TASKS
        tasks/trajectory_generator.cpp
        tasks/command_sender.cpp
        tasks/print_to_files.cpp
        tasks/ui.cpp
        )

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./include)

ADD_SUBDIRECTORY(interpolation)

ADD_EXECUTABLE(simple_motion main.cpp global_variables.cpp ${ALL_TASKS})

TARGET_LINK_LIBRARIES(simple_motion interpolator)
TARGET_LINK_LIBRARIES(simple_motion native xenomai pthread rt)


ADD_EXECUTABLE(ui main_ui.cpp)
TARGET_LINK_LIBRARIES(ui native xenomai pthread rt)
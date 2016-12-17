AUX_SOURCE_DIRECTORY(./tasks ALL_TASKS)

ADD_EXECUTABLE(simple_motion main.cpp global_variables.cpp ${ALL_TASKS})

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./include)

ADD_SUBDIRECTORY(interpolation)

TARGET_LINK_LIBRARIES(simple_motion interpolation jsoncpp)
TARGET_LINK_LIBRARIES(simple_motion native xenomai pthread rt)

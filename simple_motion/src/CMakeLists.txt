
find_package(XENOMAI REQUIRED)
find_package(ODE REQUIRED)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./include)
INCLUDE_DIRECTORIES(${XENOMAI_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ODE_INCLUDE_DIRS})

LINK_DIRECTORIES(${XENOMAI_LIBRARIES_DIRS})
LINK_DIRECTORIES(${ODE_LIBRARIES_DIRS})

AUX_SOURCE_DIRECTORY(./tasks ALL_TASKS)

ADD_EXECUTABLE(simple_motion main.cpp global_variables.cpp ${ALL_TASKS})

ADD_SUBDIRECTORY(interpolation)

TARGET_LINK_LIBRARIES(simple_motion ${DRAWSTUFF_ODE_LIBS})
TARGET_LINK_LIBRARIES(simple_motion interpolation jsoncpp)
TARGET_LINK_LIBRARIES(simple_motion ${XENOMAI_NATIVE_SKIN_LIBS})

# =========== TEST ===========
find_package(CppUnit)
if (CPPUNIT_FOUND)
    message("CppUnit found")
    AUX_SOURCE_DIRECTORY(./test TEST_FILES)
    ADD_EXECUTABLE(unit_test unit_test.cpp ${TEST_FILES})
    target_link_libraries(unit_test interpolation)
    target_link_libraries(unit_test ${CPPUNIT_LIBRARY})
else ()
    message("CppUnit not found")
endif ()
aux_source_directory(. SRC_FILES)

ADD_EXECUTABLE(main ${SRC_FILES} TSensor.hpp Sensor.cpp Sensor.h)

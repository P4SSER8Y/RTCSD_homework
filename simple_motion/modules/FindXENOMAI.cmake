find_path(XENOMAI_ROOT_DIR
        NAMES xenomai/include/xeno_config.h
        PATHS /usr /usr/local)

IF (XENOMAI_ROOT_DIR)
    MESSAGE("Xenomai found")
    SET(XENOMAI_FOUND True)
    SET(XENOMAI_INCLUDE_DIRS ${XENOMAI_ROOT_DIR}/xenomai/include)
    SET(XENOMAI_LIBRARIES_DIRS ${XENOMAI_ROOT_DIR}/xenomai/lib)
    SET(XENOMAI_NATIVE_SKIN_LIBS native xenomai pthread rt)
ENDIF ()

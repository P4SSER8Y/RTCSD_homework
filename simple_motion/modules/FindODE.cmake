find_path(ODE_ROOT_DIR
        NAMES include/ode/ode.h
        PATHS /usr /usr/local)

IF (ODE_ROOT_DIR)
    MESSAGE("Open Dynamics Engine found")
    SET(ODE_FOUND True)
    SET(ODE_INCLUDE_DIRS ${ODE_ROOT_DIR}/include)
    SET(ODE_LIBRARIES_DIRS ${ODE_ROOT_DIR}/lib)
    SET(ODE_LIBS ode)
ENDIF ()

find_path(DRAWSTUFF_ROOT_DIR
        NAMES include/drawstuff/drawstuff.h
        PATHS /usr /usr/local)

IF (DRAWSTUFF_ROOT_DIR)
    MESSAGE("Drawstuff found")
    SET(DRAWSTUFF_FOUND True)
    SET(DRAWSTUFF_ODE_LIBS drawstuff ode X11 GL GLU m)
ENDIF ()
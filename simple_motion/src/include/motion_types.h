#pragma once

#ifndef __SRC_MOTION_TYPES_H_
#define __SRC_MOTION_TYPES_H_

// Data Type
typedef struct
{
    bool Request;
    bool Response;
    bool Done;
    double Position;
    double Velocity;
    double Acceleration;
    double Deceleration;
    double Jerk;
} tPosCmd;

typedef struct
{
    double Position;
    double Velocity;
} tAxisSetpoint;

#endif

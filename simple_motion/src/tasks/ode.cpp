//
// Created by troy on 12/21/16.
//

#include "ode.h"

#include <native/task.h>
#include <rtdk.h>

#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#include <global_variables.h>
#include <include/global_variables.h>

namespace task {
namespace ode {

dWorldID world;
dBodyID sphere;
dMass mass_sphere;
const float kTimeStep = 0.1;

static void start() {
    static float xyz[3] = {0, 0, 100};
    static float hpr[3] = {90, -90, 0.0f};
    dsSetViewpoint(xyz, hpr);
}

static void simLoop(int pause) {
    const float r = 2;
    const float kScaleFactor = 150.0;
    dWorldStep(world, kTimeStep);
    double pos[3] = {axis_x.position / kScaleFactor, axis_y.position / kScaleFactor, r};
    auto rot = dBodyGetRotation(sphere);
    dsDrawSphereD(pos, rot, r);
}

void main(void *arg) {
    rt_task_set_periodic(NULL, TM_NOW, (RTIME) 1e8); // Period: 0.1s

    rt_printf("[ode] initializing...");
    dInitODE();
    rt_printf("done\n");

    // === create world ===
    rt_printf("[ode] creating world...");
    world = dWorldCreate();
    dWorldSetGravity(world, 0, 0, -9.8);
    dWorldSetCFM(world, 1e-4);
    rt_printf("done\n");

    // === create a ball ===
    rt_printf("[ode] creating ball...");
    sphere = dBodyCreate(world);
    dMassSetSphere(&mass_sphere, 1, 2);
    dBodySetMass(sphere, &mass_sphere);

    dBodySetPosition(sphere, 0, 0, 100);
    dBodySetLinearVel(sphere, 0, 0, 5);
    rt_printf("done\n");

    // === create drawstuff env ===
    dsFunctions fn;
    fn.version = DS_VERSION;
    fn.start = &start;
    fn.step = &simLoop;
    fn.stop = nullptr;
    fn.command = nullptr;
    fn.path_to_textures = "./textures";

    dsSimulationLoop(0, nullptr, 640, 640, &fn);

    terminated = true;
    dBodyDestroy(sphere);
    dWorldDestroy(world);
    dCloseODE();
}

}
}
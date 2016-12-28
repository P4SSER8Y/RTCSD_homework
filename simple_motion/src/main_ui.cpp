//
// Created by troy on 12/17/16.
//

#include <iostream>
#include <fstream>

#include <native/pipe.h>
#include <zconf.h>

int main(int argc, char **argv) {
    if (argc < 2)
        exit(1);

    FILE *pipe;
    pipe = fopen("/proc/xenomai/registry/native/pipes/simple_motion_ui", "w+");
    if (!pipe)
        exit(2);
    fputs("hello", pipe);
    fflush(pipe);
    fclose(pipe);
}

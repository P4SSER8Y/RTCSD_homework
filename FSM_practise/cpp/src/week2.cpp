//
// Created by troy on 12/2/16.
//

#include <iostream>
#include <signal.h>
#include "FSM.h"
#include "unistd.h"
#include "Sensor.h"

// In order to check the whole model, all the sensors are set to true
BoolSensor CarIn{true};
BoolSensor CarOut{true};
BoolSensor TopSensor{true};
BoolSensor BottomSensor{true};

void SignalProcess(int n) {
    std::cerr << "Catch Signal No." << n << std::endl;
    exit(0);
}

void S1_Entry(void) {
    std::cout << "Light: Red" << std::endl;
    std::cout << "Motor: Stop" << std::endl;
}

void S2_Entry(void) {
    std::cout << "Light: Red" << std::endl;
    std::cout << "Motor: Forward Revolute" << std::endl;
}
void S3_Entry(void) {
    std::cout << "Light: Green" << std::endl;
    std::cout << "Motor: Stop" << std::endl;
}

void S4_Entry(void) {
    std::cout << "Light: Green" << std::endl;
    std::cout << "Motor: Backward Revolute" << std::endl;
}

int main(int argc, char **argv) {
    signal(SIGINT, SignalProcess);
    signal(SIGTERM, SignalProcess);

    State S1{"Idle"};
    State S2{"Barrier Rising"};
    State S3{"Car Driving"};
    State S4{"Barrier Falling"};

    S1.SetEntry(&S1_Entry);
    S1.Add(std::bind(&BoolSensor::IsTrue, &CarIn), &S2);

    S2.SetEntry(&S2_Entry);
    S2.Add(std::bind(&BoolSensor::IsTrue, &TopSensor), &S3);

    S3.SetEntry(&S3_Entry);
    S3.Add(std::bind(&BoolSensor::IsTrue, &CarOut), &S4);

    S4.SetEntry(&S4_Entry);
    S4.Add(std::bind(&BoolSensor::IsTrue, &BottomSensor), &S1);

    Machine simulate{&S1};

    while (1) {
        simulate.Trigger();
        sleep(1);
    }
}

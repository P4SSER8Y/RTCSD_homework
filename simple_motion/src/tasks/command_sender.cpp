//
// Created by troy on 12/10/16.
//

#include "command_sender.h"

#include <json/json.h>
#include <fstream>
#include <iostream>

#include "global_variables.h"
#include "interpolation/interpolation.h"
#include "interpolation/trapezoid_interpolation.h"
#include "interpolation/linear_interpolation.h"

namespace task {
namespace command_sender {

int send_command_linear(RT_QUEUE &queue,
                        const double position,
                        const double velocity) {
    auto new_cmd = (LinearInterpolation **) rt_queue_alloc(&queue, sizeof(Interpolation *));
    *new_cmd = new LinearInterpolation();
    (*new_cmd)->position = position;
    (*new_cmd)->velocity = velocity;

    return rt_queue_send(&queue,
                         new_cmd,
                         sizeof(Interpolation *),
                         Q_NORMAL);
}

int send_command_trapezoid(RT_QUEUE &queue,
                           const double position,
                           const double velocity,
                           const double acceleration,
                           const double deceleration) {

    auto new_cmd = (TrapezoidInterpolation **) rt_queue_alloc(&queue, sizeof(Interpolation *));
    *new_cmd = new TrapezoidInterpolation();
    (*new_cmd)->position = position;
    (*new_cmd)->velocity = velocity;
    (*new_cmd)->acceleration = acceleration;
    (*new_cmd)->deceleration = deceleration;
    return rt_queue_send(&queue,
                         new_cmd,
                         sizeof(Interpolation *),
                         Q_NORMAL);
}

RT_QUEUE &int_to_axis_queue(const int n) {
    switch (n) {
        case 1:
            return queue_axis_x;
        case 2:
            return queue_axis_y;
    }
}

void json_parser_linear(Json::Value value) {
    RT_QUEUE &queue = int_to_axis_queue(value["axis"].asInt());
    double position = value["position"].asDouble();
    double velocity = value["velocity"].asDouble();
    send_command_linear(queue, position, velocity);
}

void json_parser_trapezoid(Json::Value value) {
    RT_QUEUE &queue = int_to_axis_queue(value["axis"].asInt());
    double position = value["position"].asDouble();
    double velocity = value["velocity"].asDouble();
    double acceleration = value["acceleration"].asDouble();
    double deceleration = value["deceleration"].asDouble();
    send_command_trapezoid(queue, position, velocity, acceleration, deceleration);
}

void main(void *arg) {
    Json::Reader reader;
    Json::Value root;
    std::ifstream is;
    is.open("commands.json", std::ios::binary);
    if (reader.parse(is, root, false))
        for (auto i = 0; i < root["interpolation"].size(); i++) {
            std::string type = root["interpolation"][i]["type"].asString();
            if (type == "linear")
                json_parser_linear(root["interpolation"][i]);
            else if (type == "trapezoid")
                json_parser_trapezoid(root["interpolation"][i]);
            else
                std::cout << "INVALID: " << i << std::endl;
        }
    is.close();
}

}
}

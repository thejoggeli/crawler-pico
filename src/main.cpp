#include <Arduino.h>
#include "Robot.h"
#include "Benchmark.h"

Robot robot;

void setup() {

    Serial.begin(115200);

    robot.init();

}

void loop() {


    Serial.println(String("L0: ") + String(robot.legs[0].joints[0].length, 3));
    Serial.println(String("L1: ") + String(robot.legs[0].joints[1].length, 3));
    Serial.println(String("L2: ") + String(robot.legs[0].joints[2].length, 3));
    Serial.println(String("L3: ") + String(robot.legs[0].joints[3].length, 3));

    float qx = 0.265;
    float qy = 0.0f;
    float qz = -0.033;
    Vector3 Q = Vector3(qx, qy, qz);
    float phi = 45.0f / 180.0f * PI;

    // float qx = 0.265;
    // float qy = 0.0f;
    // float qz = -0.033 + 0.105*(1.0/1.414)*2.0;
    // Vector3 Q = Vector3(qx, qy, qz);
    // float phi = 135.0f / 180.0f * PI;
    
    float angles_out[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    Benchmark::tick();
    Leg::IKState ikState = robot.legs[0].ik(Q, phi, angles_out);
    Benchmark::tock("ik computation time");

    if(ikState == Leg::IKState::AngleLimitsError){
        Serial.println("Leg::IKState::AngleLimitsError");
        Leg::printAngles(angles_out);
    } else if(ikState == Leg::IKState::NoSolutionError){
        Serial.println("Leg::IKState::NoSolutionError");
    } else if(ikState == Leg::IKState::OK){
        Serial.println("Leg::IKState::OK");
        Leg::printAngles(angles_out);
    } else {
        Serial.println("unhandled Leg::IKState");
    }

    delay(1000);

}
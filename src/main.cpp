#include <Arduino.h>
#include "robot/Robot.h"
#include "utils/Benchmark.h"
#include "control/GaitControl.h"
#include "control/JoystickControl.h"

Robot robot;

GaitControl gaitControl(&robot);
JoystickControl joystickControl(&robot);

void setup() {

    Serial.begin(115200);

    robot.init();
    gaitControl.init();
    joystickControl.init();
    
    robot.start();
    gaitControl.start();
    joystickControl.start();

}

void loop() {

    if(false){
     
        Serial.println(String("L0: ") + String(robot.legs[0].joints[0].length, 3));
        Serial.println(String("L1: ") + String(robot.legs[0].joints[1].length, 3));
        Serial.println(String("L2: ") + String(robot.legs[0].joints[2].length, 3));
        Serial.println(String("L3: ") + String(robot.legs[0].joints[3].length, 3));

        float qx = 0.265;
        float qy = 0.0f;
        float qz = -0.033;
        Vector3 Q = Vector3(qx, qy, qz);
        float phi = 45.0f * (1.0/180.0f) * PI;

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

    // gaitControl.update();
    // delay(1000);

    const unsigned int fps = 100;
    const unsigned long frame_duration_us = (unsigned long)((1.0/(double)fps)*1.0e6);
    unsigned long t_start_us = micros();

    // Benchmark::tick();
    joystickControl.update();
    // Benchmark::tock("joystickControl.update() duration: ");

    float used = ((double)(micros() - t_start_us) * 1.0e-6) / (double)(frame_duration_us * 1.0e-6) * 100.0;
    Serial.println("frame capacity used (%): " + String(used, 3));

    unsigned long t_duration_us = micros() - t_start_us;
    unsigned long t_delay_us = frame_duration_us - t_duration_us;
    if(t_delay_us > 0){
        delayMicroseconds(t_delay_us);
    }
    
}
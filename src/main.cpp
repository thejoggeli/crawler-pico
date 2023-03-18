#include <Arduino.h>
#include "robot/Robot.h"
#include "utils/Benchmark.h"
#include "gait/IKGait.h"

Robot robot;
IKGait gait(128);

float gaitTime = 0.0f;

void doGait(){

    Serial.println(String("IKGaitFrame at gaitTime=") + String(gaitTime, 3));

    // Benchmark::tick();
    IKGaitFrame frame;
    gait.getFrameRelativeInterp(gaitTime, frame);
    // Benchmark::tock("getFrameRelativeInterp duration: ");
    
    frame.print();

    // Benchmark::tick();
    float angles_out[NUM_JOINTS];
    for(int i = 0; i < NUM_LEGS; i++){
        robot.legs[i].ik(frame.Q[i], frame.phi[i], angles_out);
    }
    // Benchmark::tock("legs.ik() duration: ");

    gaitTime += 0.09f;
    while(gaitTime > 1.0f){
        gaitTime -= 1.0f;
    }

}

void setup() {

    Serial.begin(115200);

    robot.init();

    float gait_timestep = 1.0f / (float)(gait.numFrames);
    for(int i = 0; i < gait.numFrames; i++){

        float t = (float)(i) * gait_timestep;
        float t2pi = t * PI * 2.0f;
        float tsin = sin(t2pi);

        IKGaitFrame& frame = gait.frames[i];

        frame.Q[0].x = +0.265 * (1.0/1.414);
        frame.Q[1].x = -0.265 * (1.0/1.414);
        frame.Q[2].x = -0.265 * (1.0/1.414);
        frame.Q[3].x = +0.265 * (1.0/1.414);

        frame.Q[0].y = +0.265 * (1.0/1.414);
        frame.Q[1].y = +0.265 * (1.0/1.414);
        frame.Q[2].y = -0.265 * (1.0/1.414);
        frame.Q[3].y = -0.265 * (1.0/1.414);

        frame.Q[0].z = -0.033;
        frame.Q[1].z = -0.033;
        frame.Q[2].z = -0.033;
        frame.Q[3].z = -0.033;

        frame.phi[0] = 45.0f / 180.0f * PI;
        frame.phi[1] = 45.0f / 180.0f * PI;
        frame.phi[2] = 45.0f / 180.0f * PI;
        frame.phi[3] = 45.0f / 180.0f * PI;

        float dz = (tsin*0.5+0.5f) * (-0.05);

        frame.Q[0].z += dz;
        frame.Q[1].z += dz;
        frame.Q[2].z += dz;
        frame.Q[3].z += dz;
        
        float dphi = (tsin*0.5+0.5f) * (-15.0f) * (1.0f/180.0f) * PI;

        frame.phi[0] += dphi;
        frame.phi[1] += dphi;
        frame.phi[2] += dphi;
        frame.phi[3] += dphi; 

    }

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

    doGait();
    delay(1000);

}
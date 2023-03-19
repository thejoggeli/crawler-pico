#pragma once

#include <Arduino.h>
#include "robot/Robot.h"

class JoystickControl {
public:

    unsigned long t_start_us = 0;
    unsigned long t_passed_us = 0;
    unsigned long t_last_us = 0;
    unsigned long t_curr_us = 0;
    unsigned long t_delta_us = 0;
    float t_passed;
    float t_delta;

    Vector3 feet_base[4] = {};
    float phi_base[4] = {};
    
    Vector3 speed_offset = Vector3(1.0f, 1.0f, 1.0f);
    float speed_phi = 1.0f;
    
    Vector3 feet_offset = Vector3(0.0f, 0.0f, 0.0f);
    float phi_offset = 0.0f;

    Robot* robot;

    JoystickControl(Robot* robot){
        this->robot = robot;
    }

    void init(){

        float a = 45.0f / 180.0f * PI;
        float ax = cos(a);
        float ay = sin(a);
        float L = 0.265f;
        float H = -0.033f;

        feet_base[0] = Vector3(+L*ax, +L*ay, H);
        feet_base[1] = Vector3(-L*ax, +L*ay, H);
        feet_base[2] = Vector3(-L*ax, -L*ay, H);
        feet_base[3] = Vector3(+L*ax, -L*ay, H);

        phi_base[0] = 45.0f / 180.0f * PI;
        phi_base[1] = 45.0f / 180.0f * PI;
        phi_base[2] = 45.0f / 180.0f * PI;
        phi_base[3] = 45.0f / 180.0f * PI;

    }

    void start(){

        t_last_us = t_start_us = micros();

    }

    void update(){

        t_curr_us = micros();
        t_delta_us = t_curr_us - t_last_us;
        t_delta = t_delta_us*1.0e-6;
        t_passed_us = t_curr_us - t_start_us;
        t_passed = t_passed_us*1.0e-6;
        // Serial.println(t_delta, 3);

        Vector3 joy_offset = Vector3(0.0f, 0.0f, 0.0f);
        float joy_phi = 0.0f;

        // joy_offset.x = sin(t_passed * 2.0f * PI * 1.0) * 0.25f;

        Vector3 feet_offset_new = feet_offset + joy_offset * t_delta * speed_offset;
        float phi_offset_new = phi_offset + joy_phi * t_delta * speed_phi;

        Vector3 feet_final[4] = {
            feet_base[0] + feet_offset_new,
            feet_base[1] + feet_offset_new,
            feet_base[2] + feet_offset_new,
            feet_base[3] + feet_offset_new,
        };
        float phi_final[4] = {
            phi_base[0] + phi_offset_new,
            phi_base[1] + phi_offset_new,
            phi_base[2] + phi_offset_new,
            phi_base[3] + phi_offset_new,
        };

        float angles[NUM_LEGS][NUM_JOINTS];
        Leg::IKState ikStates[NUM_LEGS];
        bool ikFailed = false;
        for(int i = 0; i < NUM_LEGS; i++){
            // Serial.println("Q: " + feet_final[i].toString() + ", phi: " + String(phi_final[i]));
            ikStates[i] = robot->legs[i].ik(feet_final[i], phi_final[i], angles[i]);
            if(ikStates[i] != Leg::IKState::OK){
                ikFailed = true;
            }
        }

        if(!ikFailed){
            
            feet_offset = feet_offset_new;
            phi_offset = phi_offset_new;

            // move servos to new angles
            // for(int i = 0; i < NUM_LEGS; i++){
            //     Leg::printAngles(angles[i]);
            // }

        } else {

            // Serial.println("IK failed");
            // for(int i = 0; i < 4; i++){
            //     if(ikStates[i] == Leg::IKState::AngleLimitsError){
            //         Serial.println("[" + String(i) + "] AngleLimitsError");
            //     } else if(ikStates[i] == Leg::IKState::NoSolutionError){
            //         Serial.println("[" + String(i) + "] LegNoSolutionError");
            //     } else { 
            //         Serial.println("[" + String(i) + "] unhandled state");
            //     }
            // }

        }

        t_last_us = t_curr_us;

    }


};
#pragma once

#include <Arduino.h>
#include "Vector3.h"
#include "Joint.h"
#define NUM_JOINTS 4

class Leg {
public:

    enum class IKState {
        AngleLimitsError,
        NoSolutionError,
        OK,
    };

    Joint joints[NUM_JOINTS];
    Vector3 anchor;
    bool flipAnchor;

    Leg();
    Leg(const Vector3& anchor, bool flipAnchor);

    void init();
    void update();

    bool checkAngles(float angles[NUM_JOINTS]); // check if all angles are within joint limits
    void printCurrentAngles(float angles[NUM_JOINTS]); // print current angles of all joints
    static void printAngles(float angles[NUM_JOINTS]); // print angles in passed array

    Leg::IKState ik(const Vector3& Q, float phi, float angles_out[4]);

};
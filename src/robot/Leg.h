#ifndef __LEG__
#define __LEG__

#include <Arduino.h>
#include "math/Vector3.h"
#include "Joint.h"
#include "CrawlerConfig.h"

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

#endif
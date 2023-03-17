#include "Leg.h"
#include <cmath>

using namespace std;

Leg::Leg() {

}

Leg::Leg(const Vector3& anchor, bool flipAnchor) : anchor(anchor), flipAnchor(flipAnchor){

}

void Leg::init(){

}

void Leg::update(){
    
}

Leg::IKState Leg::ik(const Vector3& Q, float phi, float angles_out[4]){

    const float L0 = joints[0].length;
    const float L1 = joints[1].length;
    const float L2 = joints[2].length;
    const float L3 = joints[3].length;

    // compute point for 2-dof problem
    const float xy = sqrt(Q.x * Q.x + Q.y * Q.y) - L0 - L3 * sin(phi);
    const float z = Q.z + L3 * cos(phi);
    // Serial.println(String("xy: ") + String(xy, 6));
    // Serial.println(String("z: ") + String(z, 6));

    // solve 2-dof problem
    const float v = (xy * xy + z * z - L1 * L1 - L2 * L2) / (2.0f * L1 * L2);
    // Serial.println(String("xy * xy + z * z - L1 * L1 - L2 * L2: ") + String(xy * xy + z * z - L1 * L1 - L2 * L2, 6));
    // Serial.println(String("2.0f * L1 * L2: ") + String(2.0f * L1 * L2, 6));
    // Serial.println(String("v: ") + String(v, 6));

    if(v < -1.0f || v > 1.0f) {
        return Leg::IKState::NoSolutionError;
    }

    float a2 = -acos(v);
    float a1 = atan2(z, xy) - atan2(L2 * sin(a2), L1 + L2 * cos(a2));

    // compute angles for first and last joint 
    float a3 = phi - a1 - a2 - PI * 0.5f;
    float a0 = atan2(Q.y, Q.x);

    // write angles to output array
    angles_out[0] = a0;
    angles_out[1] = a1;
    angles_out[2] = a2;
    angles_out[3] = a3;
    
    // check angles
    if(!checkAngles(angles_out)){
        return Leg::IKState::AngleLimitsError;
    }

    return Leg::IKState::OK;

}

bool Leg::checkAngles(float angles[NUM_JOINTS]){
    for(int i = 0; i < NUM_JOINTS; i++){
        if(angles[i] < joints[i].minAngle || angles[i] > joints[i].maxAngle){
            return false;
        }
    }
    return true;
}

void Leg::printCurrentAngles(float angles[NUM_JOINTS]){
    for(int i = 0; i < NUM_JOINTS; i++){
        Serial.println(String("a") + String(i) + String(": ") + String(joints[i].angle/PI*180.0f, 6));
    }
}

void Leg::printAngles(float angles[NUM_JOINTS]){
    for(int i = 0; i < NUM_JOINTS; i++){
        Serial.println(String("a") + String(i) + String(": ") + String(angles[i]/PI*180.0f, 6));
    }
}
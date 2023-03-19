#ifndef __JOINT__
#define __JOINT__

#include <Arduino.h>

class Joint {
public:

    float angle;
    float angleOffset;
    float length;

    float minAngle = -PI*0.5f;
    float maxAngle = +PI*0.5f;

    Joint();

};

#endif
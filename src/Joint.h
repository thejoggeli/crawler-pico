#pragma once

#include <Arduino.h>

class Joint {
public:

    float angle;
    float length;

    float minAngle = -PI*0.5f;
    float maxAngle = +PI*0.5f;

    Joint();

};
#pragma once

#include <Arduino.h>
#include <cmath>
#include "Leg.h"
#define NUM_LEGS 4

class Robot {
public:

    Leg legs[NUM_LEGS];

    Robot();

    void init();
    void update();

};
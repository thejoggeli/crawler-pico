#ifndef __ROBOT__
#define __ROBOT__

#include <Arduino.h>
#include <cmath>
#include "Leg.h"
#include "CrawlerConfig.h"

class Robot {
public:

    Leg legs[NUM_LEGS];

    Robot();

    void init();
    void start();
    void update();

};

#endif

#ifndef __IK_GAIT_FRAME__
#define __IK_GAIT_FRAME__

#include "CrawlerConfig.h"
#include "math/Vector3.h"

class IKGaitFrame {
public:

    Vector3 Q[NUM_LEGS];
    float phi[NUM_LEGS];

    IKGaitFrame();

    void setZero();
    void print();

};

#endif
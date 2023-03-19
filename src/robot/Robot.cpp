#include "Robot.h"

Robot::Robot() {
    
}

void Robot::init(){

    legs[0].anchor = Vector3(+0.052, +0.052, 0.0);
    legs[1].anchor = Vector3(-0.052, +0.052, 0.0);
    legs[2].anchor = Vector3(-0.052, -0.052, 0.0);
    legs[3].anchor = Vector3(+0.052, -0.052, 0.0);

    for(int i = 0; i < NUM_LEGS; i++){
        legs[i].init();
        legs[i].joints[0].length = 0.068f;
        legs[i].joints[1].length = 0.068f;
        legs[i].joints[2].length = 0.068f;
        legs[i].joints[3].length = 0.105f;
    }

    legs[0].joints[0].angleOffset = 45.0f / 180.0f * PI;
    legs[1].joints[0].angleOffset = 135.0f / 180.0f * PI;
    legs[2].joints[0].angleOffset = -135.0f / 180.0f * PI;
    legs[3].joints[0].angleOffset = -45.0f / 180.0f * PI;
    
}

void Robot::start(){
    
}

void Robot::update(){

}
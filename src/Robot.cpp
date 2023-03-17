#include "Robot.h"

Robot::Robot() {
    
}

void Robot::init(){

    legs[0].anchor = Vector3(+0.052, +0.052, 0.0);
    legs[1].anchor = Vector3(-0.052, +0.052, 0.0);
    legs[2].anchor = Vector3(-0.052, -0.052, 0.0);
    legs[3].anchor = Vector3(+0.052, -0.052, 0.0);

    legs[0].flipAnchor = false;
    legs[1].flipAnchor = false;
    legs[2].flipAnchor = true;
    legs[3].flipAnchor = true;

    for(int i = 0; i < NUM_LEGS; i++){
        legs[i].init();
        legs[i].joints[0].length = 0.068f;
        legs[i].joints[1].length = 0.068f;
        legs[i].joints[2].length = 0.068f;
        legs[i].joints[3].length = 0.105f;
    }
    
}

void Robot::update(){

}
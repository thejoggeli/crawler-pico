#include "IKGaitFrame.h"
#include <Arduino.h>

IKGaitFrame::IKGaitFrame(){

}

void IKGaitFrame::setZero(){
    
    for(int i = 0; i < NUM_LEGS; i++){
        Q[i].x = 0.0f;
        Q[i].y = 0.0f;
        Q[i].z = 0.0f;
        phi[i] = 0.0f;
    }

}

void IKGaitFrame::print(){
    for(int i = 0; i < NUM_LEGS; i++){
        Serial.print(String("[Leg-") + String(i) + String("] "));
        Serial.print(String("Q: (") + String(Q[i].x, 3) + ", " + String(Q[i].y, 3) + ", " + String(Q[i].z, 3) + "), ");
        Serial.print(String("phi: ") + String(phi[i]*(1.0f/PI)*180.0f, 3));
        Serial.println("");
    }
}
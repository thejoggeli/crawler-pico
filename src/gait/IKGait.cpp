#include "IKGait.h"
#include <cmath>
#include <Arduino.h>

using namespace std;

IKGait::IKGait(unsigned int numFrames) : numFrames(numFrames){
    frames = new IKGaitFrame[numFrames];
}

IKGait::~IKGait(){
    delete[] frames;
}

const IKGaitFrame& IKGait::getFrameRelative(float relativeTime){
    unsigned int i = (unsigned int)(relativeTime * (float)(numFrames));
    return frames[i];
}

void IKGait::getFrameRelativeInterp(float relativeTime, IKGaitFrame& frame_out){

    float t = relativeTime * (float)(numFrames);
    float a = floor(t);
    float b = ceil(t);
    unsigned int ai = (int) a;
    unsigned int bi = (int) b;
    // Serial.println(String("ai/bi = ") + String(ai) + "/" + String(bi));
    if(ai == bi){
        for(int i = 0; i < NUM_LEGS; i++){
            frame_out.Q[i] = frames[ai].Q[i];
            frame_out.phi[i] = frames[ai].phi[i];
        }
    } else {
        if(bi >= numFrames){
            b = 0.0;
            bi = 0;
        }
        float s = t - a;
        float z = 1.0 - s;
        
        for(int i = 0; i < NUM_LEGS; i++){
            frame_out.Q[i] = frames[ai].Q[i] * z + frames[bi].Q[i] * s;
            frame_out.phi[i] = frames[ai].phi[i] * z + frames[bi].phi[i] * s;
        }
    }

}
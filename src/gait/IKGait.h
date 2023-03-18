#ifndef __IK_GAIT__
#define __IK_GAIT__

#include "IKGaitFrame.h"

class IKGait {
public:

    IKGaitFrame* frames;
    unsigned int numFrames;

    IKGait(unsigned int numFrames);
    ~IKGait();

    const IKGaitFrame& getFrameRelative(float relativeTime);
    void getFrameRelativeInterp(float relativeTime, IKGaitFrame& frame_out);

};

#endif
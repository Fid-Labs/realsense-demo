#ifndef INTEL_REAL_SENSE_H
#define INTEL_REAL_SENSE_H

#include "DepthCamera.h"

class IntelRealSense : public DepthCamera
{
public:
    bool configure(int width, int height, int fps) override;

protected:
    void captureFrame() override;

private:
    int width;
    int height;
    int fps;
};

#endif // INTEL_REAL_SENSE_H
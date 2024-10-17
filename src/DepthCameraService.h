#ifndef DEPTH_CAMERA_SERVICE_H
#define DEPTH_CAMERA_SERVICE_H

#include "DepthCamera.h"
#include <memory>

class DepthCameraService
{
public:
    DepthCameraService(std::unique_ptr<DepthCamera> camera);
    bool init(int width, int height, int fps);
    bool start();
    void stop();

private:
    std::unique_ptr<DepthCamera> camera;
};

#endif // DEPTH_CAMERA_SERVICE_H
#include "DepthCameraService.h"

DepthCameraService::DepthCameraService(std::unique_ptr<DepthCamera> camera)
    : camera(std::move(camera)) {}

bool DepthCameraService::init(int width, int height, int fps)
{
    return camera->configure(width, height, fps);
}

bool DepthCameraService::start()
{
    return camera->startStreaming();
}

void DepthCameraService::stop()
{
    camera->stopStreaming();
}
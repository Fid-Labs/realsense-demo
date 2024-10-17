#include "DepthCamera.h"
#include <iostream>
#include <chrono>

DepthCamera::DepthCamera() : isStreaming(false) {}

bool DepthCamera::startStreaming()
{
    if (isStreaming)
    {
        std::cout << "Already streaming" << std::endl;
        return false;
    }
    isStreaming = true;
    streamThread = std::thread(&DepthCamera::streamFrames, this);
    return true;
}

void DepthCamera::stopStreaming()
{
    if (!isStreaming)
    {
        return;
    }
    isStreaming = false;
    if (streamThread.joinable())
    {
        streamThread.join();
    }
}

void DepthCamera::streamFrames()
{
    while (isStreaming)
    {
        captureFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(33)); // ~30 FPS
    }
}
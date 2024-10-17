#ifndef DEPTH_CAMERA_H
#define DEPTH_CAMERA_H

#include <atomic>
#include <thread>

class DepthCamera
{
public:
    DepthCamera();
    virtual ~DepthCamera() = default;

    virtual bool configure(int width, int height, int fps) = 0;
    bool startStreaming();
    void stopStreaming();

protected:
    virtual void captureFrame() = 0;

private:
    void streamFrames();
    std::atomic<bool> isStreaming;
    std::thread streamThread;
};

#endif // DEPTH_CAMERA_H